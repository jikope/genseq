#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <genseq/Gendhing.hpp>
#include <genseq/Sequencer.hpp>
#include <genseq/NotationReader.hpp>
#include <filesystem>

const std::string output_folder{"output"};
namespace sfs = std::filesystem;

int main(int argc, char *argv[])
{
    std::cout << "GenSeq - Gendhing Sequencer\n";

    // 1. Parse notation input from command line. Things to parse:
    //    1. Title
    //    2. Laras
    //    3. Notation
    // gendhing_file = read_pdf("filename.pdf");
    // auto notation = NotationReader::PDFToNotation("ArjunaMangsah_yogya!jm.pdf");
    std::vector<std::string> notes = {
            "7", // Buka
            "2", "3", "2", "6", "2", "3", "2", "7",
            "3", "2", "6", "5", "3", "5", "6", "7",
            "7", "7", "7", "7", "6", "5", "6", "7",
            "3", "2", "6", "5", "6", "7", "5", "6", // 32
            "7", "5", "6", "0", "7", "2", "7", "6",
            "3", "5", "6", "7", "6", "5", "2", "3",
            "6", "7", "3", "2", "6", "3", "2", "7",
            "3", "2", "6", "5", "3", "5", "6", "7"
    };

    std::vector<std::string> asmarandana = {
        "6",
        "2", "1", "2", "6", "2", "1", "2", "3",
        "5", "3", "2", "1", "3", "2", "3", "1",
        "6", "3", "2", "1", "3", "2", "1", "6",
        "5", "3", "2", "1", "3", "2", "1", "6",
    };

    std::vector<std::string> ngeksiganda = {
        "5",
        "0", "6", "5", "6", "2", "3", "2", "1",
        "0", "6", "5", "6", "2", "3", "2", "1",
        "2", "6", "5", "0", "5", "6", "1", "2",
        "3", "5", "0", "2", "3", "5", "6", "5", // 32
        "0", "0", "5", "6", "7", "6", "5", "4", 
        "2", "1", "3", "2", "1", "6", "3", "5", 
        "0", "0", "5", "6", "7", "6", "5", "4", 
        "6", "5", "2", "1", "2", "3", "2", "1", // 64
        "0", "0", "1", "1", "2", "3", "2", "1", 
        "5", "6", "1", "2", "3", "2", "1", "6", 
        "2", "1", "6", "0", "2", "1", "6", "5",
        "6", "6", "2", "1", "3", "2", "6", "5" // 96
    };

    std::string title{"Sedya Asih"};
    // Gendhing gendhing{ "Pelog", Laras::Pelog, std::vector<std::string>{ "1", "2", "3", "4", "5", "6", "7"} };
    Gendhing gendhing{ "Slendro", Laras::Slendro, std::vector<std::string>{ "1", "2", "3", "5", "6", "1h"} };

    sfs::path output_path = sfs::current_path() /= output_folder;
    // Check root output path
    if (!sfs::exists(output_path)) {
        sfs::create_directory(output_folder);
        std::cout << "Creating root folder\n";
    }

    output_path /= gendhing.m_Title;
    if (!sfs::exists(output_path)) {
        sfs::create_directory(output_path);
        std::cout << "Creating gendhing folder \n";
    }

    std:: cout << (output_path) << "\n";
    // 2. Convert notation to Standard Midi File(SMF)
    // std::vector<std::string> instruments{ "Balungan", "Bonang", "Kendhang", "Kempul", "Kenong", "Slenthem" };
    Sequencer::ConvertToMidi(gendhing, output_path);


    // 3. Render SMF to WAV using sfizz_render
    std::string SARON_FILE =
        "/home/jikope/Documents/MuseScore3/SoundFonts/Gamelan "
        "SFZ/FIX_saron.sfz";
    std::string BONANG_FILE =
        "/home/jikope/Documents/MuseScore3/SoundFonts/Gamelan "
        "SFZ/BIMA_bonang.sfz";
    std::string KENONG_FILE =
        "/home/jikope/Documents/MuseScore3/SoundFonts/Gamelan "
        "SFZ/BIMA_kenong.sfz";
    std::string KEMPUL_FILE =
        "/home/jikope/Documents/MuseScore3/SoundFonts/Gamelan "
        "SFZ/FIX_kempul.sfz";
    
    Sequencer::ConvertToWav(output_path, {SARON_FILE, BONANG_FILE, KENONG_FILE, KEMPUL_FILE});

    std::cout << "Successfully rendered to " << output_folder;

    return 0;
}
