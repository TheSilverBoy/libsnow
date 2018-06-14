if(SNOW_BUILD_EXAMPLES)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)

add_executable(hello main.c)
target_include_directories(hello PRIVATE ../include)
target_link_libraries(hello PRIVATE snow_main snow)
endif()
