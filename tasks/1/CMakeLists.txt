cmake_minimum_required(VERSION 3.20)

add_library(task1 task1.cpp task1.h)

target_include_directories(task1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})