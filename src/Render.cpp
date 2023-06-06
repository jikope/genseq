#include <filesystem>
#include <spdlog/spdlog.h>
#include <fmidi/fmidi.h>
#include <st_audiofile_libs.h>
#include "MidiHelpers.h"
#include "sfizz.hpp"
#include "sfizz_private.hpp"
#include <genseq/Render.hpp>

namespace sfs = std::filesystem;

struct CallbackData {
    sfz::Sfizz& synth;
    unsigned delay;
    bool finished;
};

void midiCallback(const fmidi_event_t * event, void * cbdata) {
    auto data = reinterpret_cast<CallbackData*>(cbdata);

    if (event->type != fmidi_event_type::fmidi_event_message)
        return;

    switch (midi::status(event->data[0])) {
        case midi::noteOff:
            data->synth.noteOff(data->delay, event->data[1], event->data[2]);
            break;
        case midi::noteOn:
            if (event->data[2] == 0)
                data->synth.noteOff(data->delay, event->data[1], event->data[2]);
            else
                data->synth.noteOn(data->delay, event->data[1], event->data[2]);
            break;
        case midi::systemMessage:
            break;
    }
}

void finishedCallback(void * cbdata)
{
    auto data = reinterpret_cast<CallbackData*>(cbdata);
    data->finished = true;
}

namespace Render {
/*
 * Convert MIDI file .mid or .smf to WAV file using sfizz as synthesizer.
 * Resulting .wav file will be saved to {target_dir}/wav.
 *
 * Stolen from sfizz_render 
 * https://github.com/sfztools/sfizz/blob/develop/clients/sfizz_render.cpp
 *
 * @param target_dir Directory that store midi/ and wav/.
 * @param midi_path  Path to MIDI file.
 * @param sfz_path   Path to .sfz file.
 * @param wav_out    Output's filename.
 */
int ConvertToWav(
                 const sfs::path &target_dir,
                 const sfs::path &midi_path,
                 const sfs::path &sfz_path,
                 const sfs::path &wav_out,
                 int              sampleRate,
                 unsigned int blockSize) {

    sfz::Sfizz synth;
    synth.setSamplesPerBlock(blockSize);
    synth.setSampleRate(sampleRate);
    // synth.setSampleQuality(sfz::Synth::ProcessMode::ProcessFreewheeling, 2);
    synth.setNumVoices(64);
    synth.enableFreeWheeling();
    synth.loadSfzFile(sfz_path);

    drwav outFile;
    drwav_data_format outputFormat{};
    outputFormat.container = drwav_container_riff;
    outputFormat.format = DR_WAVE_FORMAT_PCM;
    outputFormat.channels = 2;
    outputFormat.sampleRate = sampleRate;
    outputFormat.bitsPerSample = 16;

    // TODO: Handle if error
    // WAV OUTPUT
    // fs::path outputPath = (target_dir + "/wav/" + wav_out);
    std::string outputPath = (target_dir / "wav" / wav_out);
    // spdlog::info("WAV output {} \n", outputPath.string());
    drwav_bool32 outputFileOk = drwav_init_file_write(
        &outFile, outputPath.c_str(), &outputFormat, nullptr);

    auto doubleSampleRate = static_cast<double>(sampleRate);
    const double increment{ 1 / doubleSampleRate };
    uint64_t numFramesWritten { 0 };
    sfz::AudioBuffer<float> audioBuffer { 2, blockSize };
    sfz::Buffer<float> interleavedBuffer { 2 * blockSize };
    sfz::Buffer<int16_t> interleavedPcm { 2 * blockSize };

    // MIDI INPUT
    // spdlog::info("Midi Input {} \n", (target_dir / "midi" / midi_path).c_str());
    fmidi_smf_u midiFile{ fmidi_smf_file_read( (target_dir / "midi" / midi_path).c_str() ) };
    const auto* midiInfo = fmidi_smf_get_info(midiFile.get());
    if (!midiInfo) 
        spdlog::info("Cant get info of midi file");
    fmidi_player_u midiPlayer { fmidi_player_new(midiFile.get()) };
    CallbackData callbackData { synth, 0, false };
    fmidi_player_event_callback(midiPlayer.get(), &midiCallback, &callbackData);
    fmidi_player_finish_callback(midiPlayer.get(), &finishedCallback, &callbackData);

    fmidi_player_start(midiPlayer.get());

    // Start writing on wav file
    while (!callbackData.finished) {
        for (callbackData.delay = 0; callbackData.delay < blockSize && !callbackData.finished; callbackData.delay++)
            fmidi_player_tick(midiPlayer.get(), increment);
        synth.handle()->synth.renderBlock(audioBuffer);
        sfz::writeInterleaved(audioBuffer.getConstSpan(0), audioBuffer.getConstSpan(1), absl::MakeSpan(interleavedBuffer));
        drwav_f32_to_s16(interleavedPcm.data(), interleavedBuffer.data(), 2 * blockSize);
        numFramesWritten += drwav_write_pcm_frames(&outFile, blockSize, interleavedPcm.data());
    }

    // For smooth end of file
    auto averagePower = sfz::meanSquared<float>(interleavedBuffer);
    while (averagePower > 1e-12f) {
        synth.handle()->synth.renderBlock(audioBuffer);
        sfz::writeInterleaved(audioBuffer.getConstSpan(0), audioBuffer.getConstSpan(1), absl::MakeSpan(interleavedBuffer));
        drwav_f32_to_s16(interleavedPcm.data(), interleavedBuffer.data(), 2 * blockSize);
        numFramesWritten += drwav_write_pcm_frames(&outFile, blockSize, interleavedPcm.data());
        averagePower = sfz::meanSquared<float>(interleavedBuffer);
    }

    drwav_uninit(&outFile);
    spdlog::info("Wrote {} frames of sounds", numFramesWritten);

    return 0;
}
}
