add_subdirectory(unity)

# for loading the shared library from the start instead of lazy loading
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -fno-plt")

add_executable(print_matrix print_matrix_test.c)
add_executable(matmul matmul_test.c)
add_executable(index_matrix index_matrix_test.c)
add_executable(basic_ops basic_ops_test.c)

target_link_libraries(matmul unity claw)
target_link_libraries(print_matrix unity claw)
target_link_libraries(index_matrix unity claw)
target_link_libraries(basic_ops unity claw)

add_test(NAME matmul COMMAND matmul)
add_test(NAME print_matrix COMMAND print_matrix)
add_test(NAME index_matrix COMMAND index_matrix)
add_test(NAME basic_ops COMMAND basic_ops)