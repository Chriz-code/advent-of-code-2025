cmake_minimum_required(VERSION 4.0.0)
project(advent-of-code-2025 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")

## Add Z3
set(Z3_MIN_VERSION "4.15.3")
set(Z3_BUILD_LIBZ3_SHARED FALSE)

# First, try to find Z3 on the system
find_package(Z3 ${Z3_MIN_VERSION} CONFIG QUIET)

if(Z3_FOUND)
    message(STATUS "Found system Z3 version ${Z3_VERSION_STRING}")
    # Z3_LIBRARIES will contain z3::libz3
else()
    message(STATUS "System Z3 not found or version too old, fetching Z3 ${Z3_MIN_VERSION}")
    
    # Fallback to FetchContent
    include(FetchContent)
    FetchContent_Declare(Z3
        GIT_REPOSITORY https://github.com/Z3Prover/z3
        GIT_TAG        z3-${Z3_MIN_VERSION}
    )
    FetchContent_MakeAvailable(Z3)
    
    # Add the C++ API include directory for z3++.h
    if(TARGET libz3)
        target_include_directories(libz3 INTERFACE
            $<BUILD_INTERFACE:${z3_SOURCE_DIR}/src/api/c++>
        )
    endif()
    
    # Create an alias to match the system install target name
    if(NOT TARGET z3::libz3)
        add_library(z3::libz3 ALIAS libz3)
    endif()
endif()
##

set(INPUT_FILES ${YOUR_DIRECTORY}/days)

file(COPY inputs DESTINATION ${CMAKE_BINARY_DIR})
add_executable(advent-of-code-2025 main.cpp)

target_link_libraries(advent-of-code-2025 PRIVATE z3::libz3 -static)
if(MINGW)
    add_compile_options("-Wa,-mbig-obj")
endif()

include(CTest)
enable_testing()

