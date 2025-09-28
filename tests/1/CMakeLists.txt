cmake_minimum_required(VERSION 3.20)

add_executable(test1 test1.cpp)

target_link_libraries(test1 PRIVATE GTest::gtest_main task1)

include(GoogleTest)
gtest_discover_tests(test1)
