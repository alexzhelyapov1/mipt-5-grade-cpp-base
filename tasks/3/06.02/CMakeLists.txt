# cmake_minimum_required(VERSION 3.28)

# project(RationalModules LANGUAGES CXX)


# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)


# find_program(CLANG_SCAN_DEPS_PATH NAMES clang-scan-deps-18 clang-scan-deps REQUIRED)
# set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS "${CLANG_SCAN_DEPS_PATH}" CACHE FILEPATH "Path to clang-scan-deps" FORCE)

# message(STATUS "Using clang-scan-deps: ${CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS}")


add_executable(06.02
    main.cpp
    rational.cpp
)

target_sources(06.02 PUBLIC
    FILE_SET CXX_MODULES FILES
    rational.cppm
    rational_mixins.cppm
)
