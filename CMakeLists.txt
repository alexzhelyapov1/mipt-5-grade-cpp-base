# cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..

cmake_minimum_required(VERSION 3.28)
project(cpp_coursework LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(CLANG_SCAN_DEPS_PATH NAMES clang-scan-deps-18 clang-scan-deps REQUIRED)
set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS "${CLANG_SCAN_DEPS_PATH}" CACHE FILEPATH "Path to clang-scan-deps" FORCE)
message(STATUS "Using clang-scan-deps: ${CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS}")

add_subdirectory(third-party)
add_subdirectory(tasks)
add_subdirectory(tests)
