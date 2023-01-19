cmake_minimum_required(VERSION 3.1)
project(Claw.js C)

include(CTest)

set(CMAKE_C_STANDARD 99)

file(GLOB HEADERS CONFIGURE_DEPENDS include/Claw.h include/claw/*.h)
file(GLOB SRC CONFIGURE_DEPENDS src/*.c src/*/*.c)

add_executable(use_case1-exec ${HEADERS} ${SRC})

target_include_directories(use_case1-exec PUBLIC include)

find_package(OpenCL REQUIRED)
target_link_libraries(use_case1-exec OpenCL::OpenCL)


enable_testing()
add_subdirectory(test)