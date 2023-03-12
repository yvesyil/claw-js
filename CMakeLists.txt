cmake_minimum_required(VERSION 3.1)
project(claw.js)

include(CTest)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(extern)

file(GLOB HEADERS CONFIGURE_DEPENDS include/claw.h include/claw/*.h)
file(GLOB SRC CONFIGURE_DEPENDS src/*.c src/*/*.c src/*/*/*.c)

add_library(claw SHARED ${HEADERS} ${SRC})

target_include_directories(claw PUBLIC include)

find_package(OpenCL REQUIRED)
target_link_libraries(claw OpenCL::OpenCL)
target_link_libraries(claw clblast)

enable_testing()
add_subdirectory(tests)