include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

if(SNOW_BUILD_SHARED_LIBS)
set(LIB_TYPE SHARED)
else()
set(LIB_TYPE STATIC)
endif()

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/)

add_library(snow ${LIB_TYPE} stb_image.c snow.c ../include/snow/snow.h snow_internal.h window/win32/window.c glad.c window/win32/window.h)
target_include_directories(snow PRIVATE ../include)
target_link_libraries(snow Opengl32 User32)

if(SNOW_OS_WINDOW)
if(SNOW_MSVC_COMPILER)
add_definitions(-DSNOW_BUILD)
endif()
endif()

add_library(snow_main STATIC snow_main.c)

