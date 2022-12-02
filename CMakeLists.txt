cmake_minimum_required(VERSION 3.1)
project(Claw.js C)

include(CTest)

set(CMAKE_C_STANDARD 99)

#include_directories(include)

set(SRC src/clops.h src/utils.h)

add_executable(demo1-exec src/demo1.c ${SRC})
add_executable(use_case1-exec src/use_case1.c ${SRC})

find_package(OpenCL REQUIRED)
target_link_libraries(demo1-exec OpenCL::OpenCL)
target_link_libraries(use_case1-exec OpenCL::OpenCL)

# Some libraries
add_subdirectory(include)

enable_testing()
add_subdirectory(test)