cmake_minimum_required(VERSION 3.1)
project(Claw.js C)

include(CTest)

set(CMAKE_C_STANDARD 99)

#add_subdirectory(include)

#set(HEADERS src/opencl/clops.c include/claw/utils.h include/claw/matrix.h include/claw/defines.h include/claw/error.h)
#set(SRC src/matrix.c src/utils.c src/error.c)
file(GLOB HEADERS CONFIGURE_DEPENDS include/Claw.h include/claw/*.h)
file(GLOB SRC CONFIGURE_DEPENDS src/*.c src/*/*.c)

#add_executable(demo1-exec src/demo1.c ${HEADERS} ${SRC})
add_executable(use_case1-exec ${HEADERS} ${SRC})

target_include_directories(use_case1-exec PUBLIC include)

find_package(OpenCL REQUIRED)
#target_link_libraries(demo1-exec OpenCL::OpenCL)
target_link_libraries(use_case1-exec OpenCL::OpenCL)

# Some libraries
# add_subdirectory(include)

enable_testing()
add_subdirectory(test)