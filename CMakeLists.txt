cmake_minimum_required(VERSION 4.0.0)
project(advent-of-code-2025 VERSION 0.1.0 LANGUAGES C CXX)

set(INPUT_FILES ${YOUR_DIRECTORY}/days)

file(COPY inputs DESTINATION ${CMAKE_BINARY_DIR})
add_executable(advent-of-code-2025 main.cpp)

include(CTest)
enable_testing()

