add_subdirectory(unity)

add_executable(matmul_test matmul_test.c)

target_link_libraries(matmul_test unity)

add_test(NAME matmul_test COMMAND matmul_test)