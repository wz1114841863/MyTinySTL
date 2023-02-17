FILE(GLOB source_file CONFIGURE_DEPENDS ./*.cpp )
add_library(allocator ${source_file})
target_include_directories(allocator PUBLIC .)
target_link_libraries(allocator PRIVATE iterator utils)