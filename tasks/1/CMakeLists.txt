cmake_minimum_required(VERSION 3.20)

add_library(task1 task1.cpp task1.h)

target_include_directories(task1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(02.02 02.02.cpp)

add_executable(02.03 02.03.cpp)
# target_compile_options(02.03 PRIVATE -pedantic)

add_executable(02.07 02.07.cpp)

add_executable(02.08 02.08.cpp)
add_executable(02.08-2 02.08-2.cpp)
