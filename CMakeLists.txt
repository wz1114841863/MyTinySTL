cmake_minimum_required(VERSION 3.19)
project(tinySTL)

set(CMAKE_CXX_STANDARD 14)

FILE(GLOB_RECURSE sources CONFIGURE_DEPENDS MyTinySTL/*.h )
add_executable(tinySTL main.cpp ${sources})