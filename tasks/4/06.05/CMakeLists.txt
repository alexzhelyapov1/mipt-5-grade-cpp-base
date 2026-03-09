add_library(test_v1 SHARED test_v1.cpp)
set_target_properties(test_v1 PROPERTIES PREFIX "")

add_library(test_v2 SHARED test_v2.cpp)
set_target_properties(test_v2 PROPERTIES PREFIX "")

add_executable(06.05_task 06.05.cpp)

find_package(Boost REQUIRED COMPONENTS dll)
target_link_libraries(06.05_task PRIVATE Boost::dll)
