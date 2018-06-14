#include "snow/snow.h"
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char** argv)
{
  snow_init();
  snow_window* win = snow_window_createex(
    "Devender\0", 800, 400, SNOW_WINDOW_DEFAULT | SNOW_WINDOW_VISIBLE);
	sleep(1);
  snow_window_destroy(&win);
  return 0;
}
