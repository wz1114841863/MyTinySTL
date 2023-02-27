FILE(GLOB source_file CONFIGURE_DEPENDS ./*.cpp )
add_library(test ${source_file})
target_include_directories(test PUBLIC .)
target_link_libraries(test PRIVATE allocator algorithm function iterator utils)