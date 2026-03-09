add_executable(07.04_test test.cpp)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(07.04_test PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(07.04_test)
