#ifndef NOTATIONREADER_H
#define NOTATIONREADER_H

#include <set>
#include <vector>
#include <string>
#include <filesystem>

namespace sfs = std::filesystem;

namespace NotationReader {
    std::vector<std::string> PDFToNotation(const sfs::path& pdf_path);
}

#endif /* NOTATIONREADER_H */
