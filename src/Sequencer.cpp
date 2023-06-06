#include "genseq/Instruments/Bonang.hpp"
#include "genseq/Instruments/Instruments.hpp"
#include "genseq/Instruments/Kempul.hpp"
#include "genseq/Instruments/Kenong.hpp"
#include "spdlog/spdlog.h"
#include <cstdlib>
#include <genseq/Sequencer.hpp>
#include <MidiFile.h>
#include <fstream>
#include <string>

void Sequencer::ConvertToMidi(const Gendhing& gendhing, const sfs::path& outFolder) {
    // Gendhing related variables
    auto laras = gendhing.m_Laras;
    std::string title = gendhing.m_Title;
    auto notation = gendhing.m_Notation;
    std::unordered_map<int, int> tempoChange;

    // Logs & Output folder variables
    sfs::path midiOut = outFolder / "midi";
    if (!sfs::exists(midiOut))
        sfs::create_directory(midiOut);
    std::ofstream logfile(outFolder / (title + ".log"));

    // Midifile related variables
    smf::MidiFile saron_midi, bonang_midi, kenong_midi, kempul_midi;
    int track    = 0;
    int channel  = 0;
    int ticks    = 200; // 240 ticks = 1 sec
    int velocity = 120;
    int start_tick = 0;
    int end_tick = start_tick + ticks;

    // Initialize Instruments
    Saron saron(laras);
    Bonang bonang(laras);
    Kenong kenong(laras);
    Kempul kempul(laras);

    // Instruments position
    int kethuk_beat = 2;
    int kempyang_beat = 1;
    int kenong_beat = 8;
    int kempul_beat = 12;
    int bonang_beat = 2;
    int gong_beat = 0;

    logfile << "Title: " << title << " Laras \n";
    logfile << "Num" << " - " << "Start" << " - " << "End" << " - " << "Diff\n"; 

    // Start looping through notation
    for (int i = 0; i < notation.size(); i++) {
        if (tempoChange[i] != 0) 
           ticks = ticks - tempoChange[i];

        start_tick = end_tick;
        end_tick = start_tick + ticks;

        // Kethuk
        if (i == kethuk_beat) {
            kenong_midi.addNoteOn(track, start_tick, 0, kenong["kt"], 40);
            kenong_midi.addNoteOff(track, end_tick, 0, kenong["kt"]);
            kethuk_beat += 4;
        }

        if (i == kempyang_beat && laras == Laras::Pelog) {
            kenong_midi.addNoteOn(track, start_tick, 0, kenong["kp"], 80);
            kenong_midi.addNoteOff(track, end_tick, 0, kenong["kp"]);
            kempyang_beat += 2;
        }

        // Kenong
        if (i == kenong_beat) {
            kenong_midi.addNoteOn(track, start_tick + 40, 0, kenong[notation[i]], 120);
            kenong_midi.addNoteOff(track, end_tick + 40, 0, kenong[notation[i]]);
            kenong_beat += 8;
        }

        // Kempul
        if (i == kempul_beat) {
            if (notation[i] == "0") {
                
            }
            kempul_midi.addNoteOn(track, start_tick, 0, kempul[notation[i]], 100);
            kempul_midi.addNoteOff(track, end_tick, 0, kempul[notation[i]]);
            kempul_beat += 8;
        }

        // Gong
        if (i == gong_beat) {
            kempul_midi.addNoteOn(track, start_tick, 0, kempul["G"], 120);
            kempul_midi.addNoteOff(track, end_tick + (2 * ticks), 0, kempul["G"]);
            gong_beat += 32;
        }

        // Saron
        int currentNote = saron[notation[i]];
        saron_midi.addNoteOn(track, start_tick, 0, currentNote, velocity);
        saron_midi.addNoteOff(track, end_tick, 0, currentNote);

        // Demung
        // Instrument.AddNote(midi_obj, pitch, velocity, start_tick, end_tick)
        saron_midi.addNoteOn(track, start_tick, 0, currentNote - 12, velocity);
        saron_midi.addNoteOff(track, end_tick, 0, currentNote - 12);

        // Peking
        if (i != 0) {
            saron_midi.addNoteOn(track, start_tick - (ticks / 2), 0, currentNote + 12, velocity);
            saron_midi.addNoteOff(track, end_tick - (ticks), 0, currentNote + 12);
        }
        saron_midi.addNoteOn(track, start_tick, 0, currentNote + 12, velocity);
        saron_midi.addNoteOff(track, end_tick, 0, currentNote + 12);

        // BONANG BARUNG
        // if (i != 0) {
        //     // Seleh kosong
        //     if (notation[bonang_beat] == "0") {
        //         // Gembyang
        //         if (i != bonang_beat) {
        //             bonang_midi.addNoteOn(track, start_tick - (ticks / 2), 0,
        //                                 bonang[notation[bonang_beat - 1]], velocity);
        //             bonang_midi.addNoteOff(track, end_tick - (ticks), 0,
        //                                 bonang[notation[bonang_beat - 1]]);
        //             bonang_midi.addNoteOn(track, start_tick, 0, bonang[notation[bonang_beat - 1]],
        //                                 velocity);
        //             bonang_midi.addNoteOff(track, end_tick, 0, bonang[notation[bonang_beat - 1]]);
        //         } else {
        //             bonang_midi.addNoteOn(track, start_tick - (ticks / 2), 0,
        //                                 bonang[notation[bonang_beat - 1]], velocity);
        //             bonang_midi.addNoteOff(track, end_tick - (ticks), 0,
        //                                 bonang[notation[bonang_beat - 1]]);
        //             bonang_midi.addNoteOn(track, start_tick - (ticks / 2), 0,
        //                                 bonang[notation[bonang_beat - 1] + "h"], velocity);
        //             bonang_midi.addNoteOff(track, end_tick - (ticks), 0,
        //                                 bonang[notation[bonang_beat - 1] + "h"]);
        //         }
        //     }
        //     // Seleh Dobel
        //     else if (notation[bonang_beat] == notation[bonang_beat - 1] || notation[bonang_beat] == notation[bonang_beat + 1]) {
        //         // Gembyang
        //         if (i != bonang_beat) {
        //             bonang_midi.addNoteOn(track, start_tick - (ticks / 2), 0,
        //                                 bonang[notation[bonang_beat - 1]], velocity);
        //             bonang_midi.addNoteOff(track, end_tick - (ticks), 0,
        //                                 bonang[notation[bonang_beat - 1]]);
        //             bonang_midi.addNoteOn(track, start_tick, 0, bonang[notation[bonang_beat - 1]],
        //                                 velocity);
        //             bonang_midi.addNoteOff(track, end_tick, 0, bonang[notation[bonang_beat - 1]]);
        //         } else {
        //             bonang_midi.addNoteOn(track, start_tick - (ticks / 2), 0,
        //                                 bonang[notation[bonang_beat - 1]], velocity);
        //             bonang_midi.addNoteOff(track, end_tick - (ticks), 0,
        //                                 bonang[notation[bonang_beat - 1]]);
        //             bonang_midi.addNoteOn(track, start_tick - (ticks / 2), 0,
        //                                 bonang[notation[bonang_beat - 1] + "h"], velocity);
        //             bonang_midi.addNoteOff(track, end_tick - (ticks), 0,
        //                                 bonang[notation[bonang_beat - 1] + "h"]);
        //         }
        //     }
        //     else {
        //         // Mipil
        //         // Tiba genep == look back | Tiba ganjil == look forward
        //         // Current: Tiba genep
        //         // Case : "23"
        //         int beat1 = std::stoi(notation[bonang_beat - 1]);
        //         int beat2 = std::stoi(notation[bonang_beat]);
        //         std::string ganjil; std::string genep;

        //         if (abs(beat1 - beat2) >= 4 && beat1 < 5) {
        //             ganjil = notation[bonang_beat - 1] + "h";
        //             genep = notation[bonang_beat];
        //         } else {
        //             if (beat1 < 5 && beat2 < 5) {
        //                 ganjil = notation[bonang_beat - 1] + "h"; // 2
        //                 genep = notation[bonang_beat] + "h";      // 3
        //             } else {
        //                 ganjil = notation[bonang_beat - 1]; // 2
        //                 genep = notation[bonang_beat];      // 3
        //             }
        //         }
        //         logfile << "MIPIL: " << ganjil << " - " << genep << "\n";
        //         bonang_midi.addNoteOn(track, start_tick - (ticks / 2), 0,
        //                             bonang[ganjil], velocity);
        //         bonang_midi.addNoteOff(track, end_tick - (ticks), 0,
        //                             bonang[ganjil]);
        //         bonang_midi.addNoteOn(track, start_tick, 0, bonang[genep],
        //                             velocity);
        //         bonang_midi.addNoteOff(track, end_tick, 0, bonang[genep]);
        //     }
        // }

        logfile << notation[i] << " - " << start_tick << " - " << end_tick << " - " << i << "\n";
        logfile << "---------------------------------------------------\n";

        if (i == bonang_beat) {
            bonang_beat += 2;
        }
    }

    saron_midi.sortTracks();
    bonang_midi.sortTracks();
    kenong_midi.sortTracks();
    kempul_midi.sortTracks();
    saron_midi.write(midiOut / "saron.mid");
    bonang_midi.write(midiOut / "bonang.mid");
    kenong_midi.write(midiOut / "kenong.mid");
    kempul_midi.write(midiOut / "kempul.mid");

    logfile.close();
}

void Sequencer::ConvertToWav(const sfs::path& target_folder, instrumen_font instruments) {
    // Logs & Output folder variables
    sfs::path wavOut = target_folder;
    if (!sfs::exists(wavOut))
        sfs::create_directory(wavOut);

    if (!sfs::exists(wavOut / "wav"))
        sfs::create_directory(wavOut / "wav");
    // std::ofstream logfile(outFolder / sfs::path(title + ".log"));

    Render::ConvertToWav(target_folder, "saron.mid",  instruments.SARON_FILE, "SARON.WAV", 22050, 1024);
    Render::ConvertToWav(target_folder, "bonang.mid", instruments.BONANG_FILE, "BONANG.WAV", 22050, 1024);
    Render::ConvertToWav(target_folder, "kenong.mid", instruments.KENONG_FILE, "KENONG.WAV", 22050, 1024);
    Render::ConvertToWav(target_folder, "kempul.mid", instruments.KEMPUL_FILE, "KEMPUL.WAV", 22050, 1024);
}
