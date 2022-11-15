cmake_minimum_required(VERSION 3.1)
project(Claw.js C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(claw-exec src/main.c src/clops.h src/utils.h)

find_package(OpenCL REQUIRED)
target_link_libraries(claw-exec OpenCL::OpenCL)