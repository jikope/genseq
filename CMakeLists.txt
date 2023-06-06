cmake_minimum_required(VERSION 3.20)

project(GenSeq
  VERSION 0.0
  LANGUAGES CXX
)

set(CXX_STANDARD_REQUIRED 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(extern/spdlog)
add_subdirectory(extern/sfizz)
add_subdirectory(extern/midifile)

add_subdirectory(src/)
add_subdirectory(app/)

# Tests ?
# add_subdirectory(tests/)
