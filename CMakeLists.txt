# cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ..

cmake_minimum_required(VERSION 3.20)
project(cpp_coursework)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(third-party)
add_subdirectory(tasks)
add_subdirectory(tests)
