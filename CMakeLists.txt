if(CMAKE_SYSTEM_NAME MATCHES "Android")
    cmake_minimum_required(VERSION 3.7.2)
else()
    cmake_minimum_required(VERSION 3.0.2)
endif()

# define a macro that helps defining an option
macro(snow_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

project(libsnow LANGUAGES C)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(${CMAKE_MODULE_PATH}/config.cmake)
include(${CMAKE_MODULE_PATH}/macros.cmake)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

if(NOT (SNOW_OS_IOS OR SNOW_OS_ANDROID))
    snow_set_option(SNOW_BUILD_SHARED_LIBS TRUE BOOL "TRUE to build SNOW as shared libraries, FALSE to build it as static libraries")
else()
    if(SNOW_OS_IOS)
        set(SNOW_BUILD_SHARED_LIBS FALSE)
    elseif(SNOW_OS_ANDROID)
        set(SNOW_BUILD_SHARED_LIBS TRUE)
    endif()
endif()

if(NOT SNOW_OS_ANDROID)
    snow_set_option(SNOW_BUILD_EXAMPLES TRUE BOOL "TRUE to build the SNOW examples, FALSE to ignore them")
else()
    set(SNOW_BUILD_EXAMPLES FALSE)
endif()

snow_set_option(SNOW_BUILD_DOC FALSE BOOL "TRUE to generate the API documentation, FALSE to ignore it")
snow_set_option(SNOW_ENCODING_UNICODE FALSE BOOL "TRUE to use unicode encoding, FALSE to ignore it")
snow_set_option(SNOW_OPENGL_ES ${SNOW_OPENGL_ES} BOOL "TRUE to use an OpenGL ES implementation, FALSE to use a desktop OpenGL implementation")

message("Generationg Snow Configuration File")
configure_file("${CMAKE_SOURCE_DIR}/snow_config.h.in"
"${CMAKE_BINARY_DIR}/snow_config.h")

include_directories(${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(examples)
