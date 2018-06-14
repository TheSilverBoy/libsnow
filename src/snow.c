#include <glad/glad.h>
#include <snow_internal.h>
#include <stdio.h>
#include <stdlib.h>

snow_config sconfig;

void snow_init()
{
	gladLoadGL();
	snow_alloc_func_set(malloc);
	snow_free_func_set(free);
}

void snow_terminate()
{

}

void snow_alloc_func_set(snow_alloc_func func)
{
	sconfig.alloc_func = func;
}

void snow_free_func_set(snow_free_func func)
{
	sconfig.free_func = func;
}

