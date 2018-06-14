#include "snow/snow.h"
#include <stdio.h>
#undef main

extern int snow_main(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	return snow_main(argc, argv);
}

