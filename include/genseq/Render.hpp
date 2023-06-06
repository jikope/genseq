#ifndef RENDER_H
#define RENDER_H

// #include <ghc/fs_std.hpp>
#include <filesystem>
#include <cstdint>
#include <string>

namespace sfs = std::filesystem;
namespace Render {
    // Driver function
    int ConvertToWav(
                     const sfs::path &target_dir,
                     const sfs::path &midi_path,
                     const sfs::path &sfz_path,
                     const sfs::path &wav_out,
                     int sampleRate,
                     unsigned int blockSize
);
}
#endif /* RENDER_H */
