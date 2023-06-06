file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${GenSeq_SOURCE_DIR}/include/GenSeq/*.hpp")

set(SOURCES_LIST
  NotationReader.cpp
  Instrument.cpp
  Sequencer.cpp
  Render.cpp
)

add_library(genseq ${SOURCES_LIST} ${HEADER_LIST})

target_include_directories(genseq
  PUBLIC ../include
  PUBLIC ../extern/sfizz/src
  PUBLIC ../extern/midifile/include
)

target_link_libraries(genseq PRIVATE
  midifile
  # pdfmm_static
  # podofo 
  sfizz::sfizz sfizz::cxxopts sfizz::internal sfizz::fmidi st_audiofile_formats
  spdlog::spdlog)

# All users of this library will need at least C++11
target_compile_features(genseq PUBLIC cxx_std_17)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

