#include "window.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void
switch_to_fullscreen(snow_window* window);

WNDCLASSEXW wnd;

snow_uint win_count = 0;
int  handle_count = 0;

const wchar_t snow_class_name[] = L"snowwindow";

static void
register_winclass()
{
  wnd.cbSize = sizeof(WNDCLASSEXW);
  wnd.style = 0;
  wnd.lpszClassName = snow_class_name;
  wnd.lpszMenuName = L"";
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
  wnd.hIcon = LoadIcon(NULL, IDC_ICON);
  wnd.hInstance = NULL;
  wnd.lpfnWndProc = WndProc;
  wnd.hIconSm = NULL;

  RegisterClassExW(&wnd);
}

static void
create_context(snow_window* window)
{
  PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR),
                                1,
                                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                                  PFD_DOUBLEBUFFER,
                                // Flags
                                PFD_TYPE_RGBA,
                                // The kind of framebuffer. RGBA or palette.
                                32,
                                // Colordepth of the framebuffer.
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                0,
                                24,
                                // Number of bits for the depthbuffer
                                8,
                                // Number of bits for the stencilbuffer
                                0,
                                // Number of Aux buffers in the framebuffer.
                                PFD_MAIN_PLANE,
                                0,
                                0,
                                0,
                                0 };

  window->device_context = GetDC(window->winhandle);

  int letWindowsChooseThisPixelFormat;
  letWindowsChooseThisPixelFormat =
    ChoosePixelFormat(window->device_context, &pfd);
  SetPixelFormat(window->device_context, letWindowsChooseThisPixelFormat, &pfd);

  window->window_context = wglCreateContext(window->device_context);
  wglMakeCurrent(window->device_context, window->window_context);
  SwapBuffers(window->device_context);
}

snow_window*
snow_window_create(snow_char* title, int w, int h)
{
  return snow_window_createex(title,
                              w,
                              h,
                              SNOW_WINDOW_VISIBLE | SNOW_WINDOW_OPENGL |
                                SNOW_WINDOW_TITLEBAR | SNOW_WINDOW_CLOSE);
}

snow_window*
snow_window_createm(snow_char* title, snow_monitor* monitor)
{
  return snow_window_create(title, monitor->w, monitor->h);
}

snow_window*
snow_window_createex(snow_char* title, int w, int h, snow_uint32 win_flags)
{
  boolean make_context = SNOW_FALSE;
  DWORD win32_flags = 0;
  if (win_flags & SNOW_WINDOW_BORDERLESS)
    win32_flags |= WS_POPUP;
  if (win_flags & SNOW_WINDOW_OPENGL)
    make_context = SNOW_TRUE;
  if (win_flags & SNOW_WINDOW_VISIBLE)
    win32_flags |= WS_VISIBLE;
  if (win_flags & SNOW_WINDOW_TITLEBAR)
    win32_flags |= WS_CAPTION | WS_MINIMIZEBOX;
  if (win_flags & SNOW_WINDOW_RESIZABLE)
    win32_flags |= WS_THICKFRAME | WS_MAXIMIZEBOX;
  if (win_flags & SNOW_WINDOW_CLOSE)
    win32_flags |= WS_SYSMENU;
  register_winclass();

  snow_window* win = sconfig.alloc_func(sizeof *win);
  win->w = w;
  win->h = h;
  win->flags = win_flags;
	
#ifndef SNOW_ENCODING_UNICODE
  wchar_t title_buffer[4056];
  mbstowcs(&title_buffer[0], title, sizeof(char)*14);
#else
  wchar_t* title_buffer = title;
#endif
  win->winhandle = CreateWindowExW(0,
                                   snow_class_name,
                                   title_buffer,
                                   win32_flags,
                                   CW_USEDEFAULT,
                                   CW_USEDEFAULT,
                                   w,
                                   h,
                                   NULL,
                                   NULL,
                                   NULL,
                                   NULL);
  if (!win->winhandle)
    return NULL;
	win->is_open = SNOW_TRUE;
	win->id = win_count++;
	++handle_count;
  if (win_flags & SNOW_WINDOW_FULLSCREEN)
    switch_to_fullscreen(win);
  if (make_context)
    create_context(win);
  return win;
}

snow_window*
snow_window_createexm(snow_char* title,
                      snow_monitor* monitor,
                      snow_uint32 win_flags)
{
  return snow_window_createex(title, monitor->w, monitor->h, win_flags);
}

void
snow_window_destroy(snow_window** win)
{
	if (win == NULL || *win == NULL) return;
	snow_window* w = *win;
	if (w->flags & SNOW_WINDOW_OPENGL)
	{
		wglDeleteContext(w->window_context);
		wglMakeCurrent(NULL, NULL);
	}
	DestroyWindow(w->winhandle);
	--win_count; --handle_count;
	sconfig.free_func(*win);
	*win = NULL;
}

snow_uint
snow_window_width_get(snow_window* win)
{
	return win->w;
}

snow_uint
snow_window_height_get(snow_window* win)
{
	return win->h;
}

snow_bool
snow_window_is_open(snow_window* win)
{
	return win->is_open;
}

void
snow_window_events_poll(snow_window* win, snow_events* events)
{
	
}

snow_window*
snow_window_clone(snow_window* win)
{
	snow_window* new = sconfig.alloc_func(sizeof* new);
	memcpy(new, win, sizeof(snow_window));
	return new;
}

void
switch_to_fullscreen(snow_window* win)
{}

LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return DefWindowProc(hwnd, msg, wparam, lparam);
}
