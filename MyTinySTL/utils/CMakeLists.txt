FILE(GLOB source_file CONFIGURE_DEPENDS ./*.cpp )
add_library(utils ${source_file})
target_include_directories(utils PUBLIC .)