#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "genseq/Gendhing.hpp"
#include "genseq/Render.hpp"
#include <filesystem>

namespace sfs = std::filesystem;

struct instrumen_font {
  std::string SARON_FILE;
  std::string BONANG_FILE;
  std::string KENONG_FILE;
  std::string KEMPUL_FILE;
};

namespace Sequencer {
// namespace sfs = fs::filesystem;
void ConvertToMidi(const Gendhing &gendhing, const sfs::path &outFolder);
void ConvertToWav(const sfs::path &target_folder, instrumen_font instruments);
} // namespace Sequencer

#endif /* SEQUENCER_H */
