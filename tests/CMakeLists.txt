add_subdirectory(unity)

add_executable(print_matrix print_matrix_test.c)
add_executable(matmul matmul_test.c)

target_link_libraries(matmul unity claw)
target_link_libraries(print_matrix unity claw)

add_test(NAME matmul COMMAND matmul)
add_test(NAME print_matrix COMMAND print_matrix)