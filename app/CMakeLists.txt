add_executable(app main.cpp)
target_compile_features(app PRIVATE cxx_std_20)

# target_include_directories(app
#   PUBLIC ../extern/spdlog/include
# )

target_link_libraries(app PRIVATE genseq)
