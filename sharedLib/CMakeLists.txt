
# To compile & build, run these commands within the cmake-build-debug directory:
# mkdir cmake-build-debug
# cmake .. && make all

cmake_minimum_required(VERSION 3.20)
set(CMAKE_C_COMPILER "clang")
project(script)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_C_FLAGS "-Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3 -s")

add_library(${PROJECT_NAME} SHARED script.h script.c)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER script.h)
