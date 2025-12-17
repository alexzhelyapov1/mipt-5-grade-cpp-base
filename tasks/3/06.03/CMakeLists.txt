find_program(BASH_EXECUTABLE bash REQUIRED)
configure_file(benchmark.sh ${CMAKE_CURRENT_BINARY_DIR}/benchmark.sh COPYONLY)
execute_process(COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/benchmark.sh)

add_custom_target(run_benchmark
    COMMAND ${BASH_EXECUTABLE} ./benchmark.sh ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running benchmark: Headers vs Modules..."
    VERBATIM
)
