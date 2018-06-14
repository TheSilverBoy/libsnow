#ifndef SNOW_WINDOW_H
#define SNOW_WINDOW_H

#include "snow_internal.h"

#ifdef SNOW_OS_WINDOWS
#include <windows.h>
#endif

SNOW_API snow_uint win_count;
SNOW_API int  handle_count;

typedef struct snow_window
{
	boolean is_open;
	boolean fullscreen;
	int id;
	int w, h;
	snow_uint32 flags;
	HWND winhandle;
	HDC device_context;
	HGLRC window_context;
} snow_window;

#endif // SNOW_WINDOW_H
