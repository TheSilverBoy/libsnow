
# detect the OS
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(SNOW_OS_WINDOWS 1)

    # don't use the OpenGL ES implementation on Windows
    set(SNOW_OPENGL_ES 0)

    # detect the architecture (note: this test won't work for cross-compilation)
    include(CheckTypeSize)
    check_type_size(void* SIZEOF_VOID_PTR)
    if(${SIZEOF_VOID_PTR} STREQUAL "4")
        set(SNOW_ARCH_32BITS 1)
    elseif(${SIZEOF_VOID_PTR} STREQUAL "8")
        set(SNOW_ARCH_64BITS 1)
    else()
        message(FATAL_ERROR "Unsupported architecture")
        return()
    endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(SNOW_OS_UNIX 1)
    if(ANDROID)
        set(SNOW_OS_ANDROID 1)
        # use the OpenGL ES implementation on Android
        set(SNOW_OPENGL_ES 1)
    else()
        set(SNOW_OS_LINUX 1)
        # don't use the OpenGL ES implementation on Linux
        set(SNOW_OPENGL_ES 0)
    endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "^k?FreeBSD$")
    set(SNOW_OS_FREEBSD 1)
    # don't use the OpenGL ES implementation on FreeBSD
    set(SNOW_OPENGL_ES 0)
elseif(CMAKE_SYSTEM_NAME MATCHES "^OpenBSD$")
    set(SNOW_OS_OPENBSD 1)
    # don't use the OpenGL ES implementation on OpenBSD
    set(SNOW_OPENGL_ES 0)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    if(IOS)
        set(SNOW_OS_IOS 1)

        # use the OpenGL ES implementation on iOS
        set(SNOW_OPENGL_ES 1)
    else()
        set(SNOW_OS_MACOSX 1)

        # don't use the OpenGL ES implementation on Mac OS X
        set(SNOW_OPENGL_ES 0)

        # detect OS X version. (use '/usr/bin/sw_vers -productVersion' to extract V from '10.V.x'.)
        EXEC_PROGRAM(/usr/bin/sw_vers ARGS -productVersion OUTPUT_VARIABLE MACOSX_VERSION_RAW)
        STRING(REGEX REPLACE "10\\.([0-9]+).*" "\\1" MACOSX_VERSION "${MACOSX_VERSION_RAW}")
        if(${MACOSX_VERSION} LESS 7)
            message(FATAL_ERROR "Unsupported version of OS X: ${MACOSX_VERSION_RAW}")
            return()
        endif()
    endif()
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Android")
    set(SNOW_OS_ANDROID 1)

    # use the OpenGL ES implementation on Android
    set(SNOW_OPENGL_ES 1)
# comparing CMAKE_SYSTEM_NAME with "CYGWIN" generates a false warning depending on the CMake version
# let's avoid it so the actual error is more visible
elseif(${CYGWIN})
    message(FATAL_ERROR "Unfortunately SNOW doesn't support Cygwin's 'hybrid' status between both Windows and Linux derivatives.\nIf you insist on using the GCC, please use a standalone build of MinGW without the Cygwin environment instead.")
else()
    message(FATAL_ERROR "Unsupported operating system or environment")
    return()
endif()

# detect the compiler and its version
# Note: on some platforms (OS X), CMAKE_COMPILER_IS_GNUCXX is true
# even when CLANG is used, therefore the Clang test is done first
if(CMAKE_C_COMPILER MATCHES "clang[+][+]" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
   # CMAKE_CXX_COMPILER_ID is an internal CMake variable subject to change,
   # but there is no other way to detect CLang at the moment
   set(SNOW_COMPILER_CLANG 1)
elseif(CMAKE_COMPILER_IS_GNUC)
    set(SNOW_COMPILER_GCC 1)
elseif(MSVC)
    set(SNOW_COMPILER_MSVC 1)
    if(MSVC_VERSION EQUAL 1400)
        set(SNOW_MSVC_VERSION 8)
    elseif(MSVC_VERSION EQUAL 1500)
        set(SNOW_MSVC_VERSION 9)
    elseif(MSVC_VERSION EQUAL 1600)
        set(SNOW_MSVC_VERSION 10)
    elseif(MSVC_VERSION EQUAL 1700)
        set(SNOW_MSVC_VERSION 11)
    elseif(MSVC_VERSION EQUAL 1800)
        set(SNOW_MSVC_VERSION 12)
    elseif(MSVC_VERSION EQUAL 1900)
        set(SNOW_MSVC_VERSION 14)
    endif()
elseif(MINGW)
    set(SNOW_COMPILER_MINGW 1)
else()
    message(FATAL_ERROR "Unsupported compiler")
    return()
endif()







