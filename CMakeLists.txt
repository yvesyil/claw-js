cmake_minimum_required(VERSION 3.1)
project(Claw.js C)

include(CTest)
include(scripts/kernel2str.cmake)

kernel2str(src/opencl/kernel/matmul1.cl)

set(CMAKE_C_STANDARD 99)

file(GLOB HEADERS CONFIGURE_DEPENDS include/claw.h include/claw/*.h)
file(GLOB SRC CONFIGURE_DEPENDS src/*.c src/*/*.c src/*/*/*.c)

add_library(claw SHARED ${HEADERS} ${SRC})

target_include_directories(claw PUBLIC include)

find_package(OpenCL REQUIRED)
target_link_libraries(claw OpenCL::OpenCL)

enable_testing()
add_subdirectory(tests)