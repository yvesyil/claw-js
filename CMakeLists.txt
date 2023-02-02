cmake_minimum_required(VERSION 3.1)
project(claw.js C)

include(CTest)
include(scripts/kernel2str.cmake)

kernel2str(src/opencl/kernel/matmul1.cl)

set(CMAKE_C_STANDARD 99)

add_subdirectory(extern)

file(GLOB HEADERS CONFIGURE_DEPENDS extern/*.h include/claw.h include/claw/*.h)
file(GLOB SRC CONFIGURE_DEPENDS src/*.c src/*/*.c src/*/*/*.c)

add_library(claw SHARED ${HEADERS} ${SRC})

target_include_directories(claw PUBLIC include)
target_include_directories(claw PUBLIC extern)

find_package(OpenCL REQUIRED)
target_link_libraries(claw OpenCL::OpenCL)
target_link_libraries(claw clblast)

enable_testing()
add_subdirectory(tests)