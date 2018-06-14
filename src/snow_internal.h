#ifndef SNOW_INTERNAL_H
#define SNOW_INTERNAL_H

#ifdef SNOW_H
#error snow.h is already included in snow_internal.h include snow_internal.h first
#endif

// define at top to make all the code implementation specific
#define SNOW_IMPL

#include "snow/snow.h"

typedef struct snow_config
{
	snow_alloc_func alloc_func;
	snow_free_func  free_func;
}snow_config;

SNOW_API snow_config sconfig;

#endif // !SNOW_INTERNAL_H
