FILE(GLOB source_file CONFIGURE_DEPENDS ./*.cpp )
FILE(GLOB source_head_file CONFIGURE_DEPENDS ./*.h)
add_library(allocator ${source_file} ${source_head_file})
target_include_directories(allocator PUBLIC .)
target_link_libraries(allocator PRIVATE iterator utils)