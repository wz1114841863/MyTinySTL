cmake_minimum_required(VERSION 3.19)
project(tinySTL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare \
    -Wno-unused-but-set-variable -Wno-array-bounds \
    -fexec-charset=GBK -finput-charset=UTF-8")

add_executable(tinySTL main.cpp)

add_subdirectory(MyTinySTL)
add_subdirectory(Test)
target_link_libraries(tinySTL PRIVATE test allocator iterator utils )