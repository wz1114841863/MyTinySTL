cmake_minimum_required(VERSION 3.19)
project(tinySTL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare \
    -Wno-unused-but-set-variable -Wno-array-bounds \
    -fexec-charset=GBK -finput-charset=UTF-8")

FILE(GLOB_RECURSE sources CONFIGURE_DEPENDS MyTinySTL/*.h )
FILE(GLOB_RECURSE test_sources CONFIGURE_DEPENDS Test/*.h )
add_executable(tinySTL main.cpp ${sources} ${test_sources})