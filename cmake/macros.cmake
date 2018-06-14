include(CMakeParseArguments)


macro(snow_add_library target)
cmake_parse_arguments(THIS "STATIC;SHARED" "" "SOURCES" ${ARGN})
if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling sfml_add_library: ${THIS_UNPARSED_ARGUMENTS}")
endif()

if(THIS_STATIC)
add_library(${target} STATIC ${THIS_SOURCES})
else()
add_library(${target} SHARED ${THIS_SOURCES})
endif()

string(REPLACE "-" "_" NAME_UPPER "${target}")
string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

endmacro()













