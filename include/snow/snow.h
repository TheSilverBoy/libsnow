#ifndef SNOW_H
#define SNOW_H

#include "snow_config.h"

#define SNOW_TRUE 1
#define SNOW_FALSE 0

#define main snow_main

typedef unsigned char snow_uint8;
typedef unsigned char snow_ubyte;
typedef unsigned int  snow_uint;
typedef unsigned long snow_uint32;
typedef unsigned short snow_uint16;

typedef snow_uint8 snow_bool;

// @brief opaque window structure
typedef struct snow_window snow_window;
typedef struct snow_monitor snow_monitor;
typedef struct snow_events snow_events;
typedef snow_uint snow_keycode;
typedef snow_uint snow_scancode;
typedef struct snow_keyboardstate snow_keyboardstate;
typedef snow_uint snow_mouse_buttontype;
typedef struct snow_mousestate snow_mousestate;
typedef struct snow_touchstate snow_touchstate;

typedef struct snow_vec2i snow_vec2i;
typedef struct snow_vec2f snow_vec2f;
typedef struct snow_vec2u snow_vec2u;

typedef struct snow_vec3i snow_vec3i;
typedef struct snow_vec3f snow_vec3f;
typedef struct snow_vec3u snow_vec3u;

typedef struct snow_vec4i snow_vec4i;
typedef struct snow_vec4f snow_vec4f;
typedef struct snow_vec4u snow_vec4u;

typedef struct snow_mat4f snow_mat4f;

typedef struct snow_recti snow_recti;
typedef struct snow_rectf snow_rectf;

typedef struct snow_color snow_color;
typedef struct snow_image snow_image;
typedef struct snow_texture2d snow_texture2d;
typedef struct snow_rectangleshape snow_rectangleshape;
typedef struct snow_triangleshape snow_triangleshape;
typedef struct snow_sprite snow_sprite;
typedef struct snow_mesh snow_mesh;
typedef struct snow_camera2d snow_camera2d;
typedef struct snow_camera3d snow_camera3d;
typedef struct snow_renderstate snow_renderstate;
typedef struct snow_rendertarget snow_rendertarget;

typedef void* (*snow_alloc_func)(snow_uint size);
typedef void (*snow_free_func)(void* block);

SNOW_API void
snow_init();
SNOW_API void
snow_terminate();

SNOW_API void
snow_alloc_func_set(snow_alloc_func func);
SNOW_API void
snow_free_func_set(snow_free_func func);

// Window System
enum
{
	SNOW_WINDOW_BORDERLESS = 1,
	SNOW_WINDOW_OPENGL = 1 << 1,
	SNOW_WINDOW_FULLSCREEN = 1 << 2,
	SNOW_WINDOW_VISIBLE = 1 << 3,
	SNOW_WINDOW_TITLEBAR = 1 << 4,
	SNOW_WINDOW_RESIZABLE = 1 << 5,
	SNOW_WINDOW_CLOSE = 1 << 6,
	SNOW_WINDOW_DEFAULT = SNOW_WINDOW_OPENGL | SNOW_WINDOW_TITLEBAR | SNOW_WINDOW_RESIZABLE |SNOW_WINDOW_CLOSE| SNOW_WINDOW_VISIBLE
};

SNOW_API snow_window*
snow_window_create(snow_char* title, int w, int h);
SNOW_API snow_window*
snow_window_createm(snow_char* title, snow_monitor* monitor);
SNOW_API snow_window*
snow_window_createex(snow_char* title, int w, int h, snow_uint32 win_flags);
SNOW_API snow_window*
snow_window_createexm(snow_char* title,
                      snow_monitor* monitor,
                      snow_uint32 win_flags);
SNOW_API void
snow_window_destroy(snow_window** win);
SNOW_API snow_uint
snow_window_width_get(snow_window* win);
SNOW_API snow_uint
snow_window_height_get(snow_window* win);
SNOW_API snow_bool
snow_window_is_open(snow_window* win);
SNOW_API void
snow_window_events_poll(snow_window* win, snow_events* events);
SNOW_API snow_window*
snow_window_clone(snow_window* win);

// Primary Monitor

typedef struct snow_monitor
{
  snow_uint w, h;
} snow_monitor;

SNOW_API snow_monitor*
snow_monitor_primary_get();

// Events Types

enum
{
  SNOW_KEYDOWN_EVENT = 0x10,
  SNOW_KEYUP_EVENT = 0x11,
  SNOW_MOUSE_MOVE_EVENT = 0x12,
  SNOW_MOUSE_BUTTON_EVENT = 0x13,
  SNOW_TOUCH_EVENT = 0x14
};

// Events

typedef struct snow_events
{
  union
  {
    snow_uint type;
    struct keyboard_event
    {
      snow_uint type;
      snow_keycode key;
    } key;
    struct mouse_move_event
    {
      snow_uint type;
      int x, y;
    } mouse;
    struct mouse_button_event
    {
      snow_uint type;
      snow_uint button;
    } mouse_button;
    struct touch_event
    {
      snow_uint type;
      int x, y;
    } touch;
  };
} snow_events;

SNOW_API snow_events*
snow_events_get_global();

// Key codes
enum
{
  // Primary Letters
  SNOW_KEY_A,
  SNOW_KEY_B,
  SNOW_KEY_C,
  SNOW_KEY_D,
  SNOW_KEY_E,
  SNOW_KEY_F,
  SNOW_KEY_G,
  SNOW_KEY_H,
  SNOW_KEY_I,
  SNOW_KEY_J,
  SNOW_KEY_K,
  SNOW_KEY_L,
  SNOW_KEY_M,
  SNOW_KEY_N,
  SNOW_KEY_O,
  SNOW_KEY_P,
  SNOW_KEY_Q,
  SNOW_KEY_R,
  SNOW_KEY_S,
  SNOW_KEY_T,
  SNOW_KEY_U,
  SNOW_KEY_V,
  SNOW_KEY_W,
  SNOW_KEY_X,
  SNOW_KEY_Y,
  SNOW_KEY_Z,

  // Numbers
  SNOW_KEY_0,
  SNOW_KEY_1,
  SNOW_KEY_2,
  SNOW_KEY_3,
  SNOW_KEY_4,
  SNOW_KEY_5,
  SNOW_KEY_6,
  SNOW_KEY_7,
  SNOW_KEY_8,
  SNOW_KEY_9,

  // Control Keys
  SNOW_KEY_LCTRL,
  SNOW_KEY_RCTRL,
  SNOW_KEY_LSHIFT,
  SNOW_KEY_RSHIFT,
  SNOW_KEY_LALT,
  SNOW_KEY_RALT,
  SNOW_KEY_RETURN,
  SNOW_KEY_ESCAPE,

  // Operational Keys
  SNOW_KEY_PLUS,
  SNOW_KEY_MINUS,
  SNOW_KEY_DIVIDE,
  SNOW_KEY_MULTIPLY,

  // Directional Keys
  SNOW_KEY_UP,
  SNOW_KEY_DOWN,
  SNOW_KEY_LEFT,
  SNOW_KEY_RIGHT,

  // F keys
  SNOW_KEY_F1,
  SNOW_KEY_F2,
  SNOW_KEY_F3,
  SNOW_KEY_F4,
  SNOW_KEY_F5,
  SNOW_KEY_F6,
  SNOW_KEY_F7,
  SNOW_KEY_F8,
  SNOW_KEY_F9,
  SNOW_KEY_F10,
  SNOW_KEY_F11,
  SNOW_KEY_F12,

  // Some Special Chars
  SNOW_KEY_PERIOD,
  SNOW_KEY_SEMICOLON,
  SNOW_KEY_COMMA,
  SNOW_KEY_QUOTE,
  SNOW_KEY_DOUBLEQUOTE,
  SNOW_KEYCOUNT
};

// Scan Codes
enum
{
  // Primary Letters
  SNOW_SCANCODE_A = 0x100,
  SNOW_SCANCODE_B = 0x101,
  SNOW_SCANCODE_C = 0x102,
  SNOW_SCANCODE_D = 0x103,
  SNOW_SCANCODE_E = 0x104,
  SNOW_SCANCODE_F = 0x105,
  SNOW_SCANCODE_G = 0x106,
  SNOW_SCANCODE_H = 0x107,
  SNOW_SCANCODE_I = 0x108,
  SNOW_SCANCODE_J = 0x109,
  SNOW_SCANCODE_K = 0x10a,
  SNOW_SCANCODE_L = 0x10b,
  SNOW_SCANCODE_M = 0x10c,
  SNOW_SCANCODE_N = 0x10d,
  SNOW_SCANCODE_O = 0x10e,
  SNOW_SCANCODE_P = 0x10f,
  SNOW_SCANCODE_Q = 0x110,
  SNOW_SCANCODE_R = 0x111,
  SNOW_SCANCODE_S = 0x112,
  SNOW_SCANCODE_T = 0x113,
  SNOW_SCANCODE_U = 0x114,
  SNOW_SCANCODE_V = 0x115,
  SNOW_SCANCODE_W = 0x116,
  SNOW_SCANCODE_X = 0x117,
  SNOW_SCANCODE_Y = 0x118,
  SNOW_SCANCODE_Z = 0x119,

  // Numbers
  SNOW_SCANCODE_0 = 0x11a,
  SNOW_SCANCODE_1 = 0x11b,
  SNOW_SCANCODE_2 = 0x11c,
  SNOW_SCANCODE_3 = 0x11d,
  SNOW_SCANCODE_4 = 0x11e,
  SNOW_SCANCODE_5 = 0x11f,
  SNOW_SCANCODE_6 = 0x120,
  SNOW_SCANCODE_7 = 0x121,
  SNOW_SCANCODE_8 = 0x122,
  SNOW_SCANCODE_9 = 0x123,

  // Control Keys
  SNOW_SCANCODE_LCTRL = 0x124,
  SNOW_SCANCODE_RCTRL = 0x125,
  SNOW_SCANCODE_LSHIFT = 0x126,
  SNOW_SCANCODE_RSHIFT = 0x127,
  SNOW_SCANCODE_LALT = 0x128,
  SNOW_SCANCODE_RALT = 0x129,
  SNOW_SCANCODE_RETURN = 0x12a,
  SNOW_SCANCODE_ESCAPE = 0x12b,

  // Operational Keys
  SNOW_SCANCODE_PLUS = 0x12c,
  SNOW_SCANCODE_MINUS = 0x12d,
  SNOW_SCANCODE_DIVIDE = 0x12e,
  SNOW_SCANCODE_MULTIPLY = 0x12f,

  // Directional Keys
  SNOW_SCANCODE_UP = 0x130,
  SNOW_SCANCODE_DOWN = 0x131,
  SNOW_SCANCODE_LEFT = 0x132,
  SNOW_SCANCODE_RIGHT = 0x133,

  // F Keys
  SNOW_SCANCODE_F1 = 0x134,
  SNOW_SCANCODE_F2 = 0x135,
  SNOW_SCANCODE_F3 = 0x136,
  SNOW_SCANCODE_F4 = 0x137,
  SNOW_SCANCODE_F5 = 0x138,
  SNOW_SCANCODE_F6 = 0x139,
  SNOW_SCANCODE_F7 = 0x13a,
  SNOW_SCANCODE_F8 = 0x13b,
  SNOW_SCANCODE_F9 = 0x13c,
  SNOW_SCANCODE_F10 = 0x13d,
  SNOW_SCANCODE_F11 = 0x13e,
  SNOW_SCANCODE_F12 = 0x13f,

  // Some Special Chars
  SNOW_SCANCODE_PERIOD = 0x140,
  SNOW_SCANCODE_SEMICOLON = 0x141,
  SNOW_SCANCODE_COMMA = 0x142,
  SNOW_SCANCODE_QUOTE = 0x143,
  SNOW_SCANCODE_DOUBLEQUOTE = 0x145,
};

// Global Keyboard States
SNOW_API snow_keyboardstate*
snow_keyboardstate_get();
SNOW_API snow_bool
snow_keyboardstate_get_keystatekc(snow_keyboardstate* state, snow_keycode code);
SNOW_API snow_bool
snow_keyboardstate_get_keystatesc(snow_keyboardstate* state,
                                  snow_scancode code);

// Mouse Buttons
enum
{
  SNOW_MOUSE_LEFT_BUTTON = 0x200,
  SNOW_MOUSE_RIGHT_BUTTON = 0x201
};

// Global Mouse States
SNOW_API snow_mousestate*
snow_mousestate_get();
SNOW_API snow_bool
snow_mousestate_get_button_state(snow_mousestate* state,
                                 snow_mouse_buttontype button_type);
SNOW_API void
snow_mousestate_get_cursor_position2iv(snow_mousestate* state,
                                       snow_vec2i* out_pos);
SNOW_API void
snow_mousestate_get_cursor_position2i(snow_mousestate* state, int* w, int* h);

// Global Touch States
SNOW_API snow_touchstate*
snow_touchstate_get();
SNOW_API void
snow_touchstate_get_touch_position2iv(snow_touchstate* state,
                                      snow_vec2i* out_pos);
SNOW_API void
snow_touchstate_get_touch_position2i(snow_touchstate* state, int* w, int* h);

// Math

// Vector 2 Functions
typedef struct snow_vec2i
{
  int x, y;
} snow_vec2i;

typedef struct snow_vec2f
{
  float x, y;
} snow_vec2f;

typedef struct snow_vec2u
{
  snow_uint x, y;
} snow_vec2u;

// Addition Scalar Functions
SNOW_API snow_vec2i
snow_vec2i_adds(snow_vec2i v, int s);
SNOW_API snow_vec2f
snow_vec2f_adds(snow_vec2f v, float s);
SNOW_API snow_vec2u
snow_vec2u_addu(snow_vec2u v, snow_uint s);

// Subtraction Scalar Functions
SNOW_API snow_vec2i
snow_vec2f_subs(snow_vec2i v, int s);
SNOW_API snow_vec2f
snow_vec2u_subs(snow_vec2f v, float s);
SNOW_API snow_vec2u
snow_vec2i_subs(snow_vec2u v, snow_uint s);

// Multiplication Scalar Functions
SNOW_API snow_vec2i
snow_vec2i_mults(snow_vec2i v, int s);
SNOW_API snow_vec2f
snow_vec2f_mults(snow_vec2f v, float s);
SNOW_API snow_vec2u
snow_vec2u_mults(snow_vec2u v, snow_uint s);

// Divide Scalar Functions
SNOW_API snow_vec2i
snow_vec2i_divs(snow_vec2i v, int s);
SNOW_API snow_vec2f
snow_vec2f_divs(snow_vec2f v, float s);
SNOW_API snow_vec2u
snow_vec2u_divs(snow_vec2u v, snow_uint s);

// Addition Functions
SNOW_API snow_vec2i
snow_vec2i_add(snow_vec2i a, snow_vec2i b);
SNOW_API snow_vec2f
snow_vec2f_add(snow_vec2f a, snow_vec2f b);
SNOW_API snow_vec2u
snow_vec2u_add(snow_vec2u a, snow_vec2u b);

// Subtraction Functions
SNOW_API snow_vec2i
snow_vec2i_sub(snow_vec2i a, snow_vec2i b);
SNOW_API snow_vec2f
snow_vec2f_sub(snow_vec2f a, snow_vec2f b);
SNOW_API snow_vec2u
snow_vec2u_sub(snow_vec2u a, snow_vec2u b);

// Divide Functions
SNOW_API snow_vec2i
snow_vec2i_div(snow_vec2i a, snow_vec2i b);
SNOW_API snow_vec2f
snow_vec2f_div(snow_vec2f a, snow_vec2f b);
SNOW_API snow_vec2u
snow_vec2u_div(snow_vec2u a, snow_vec2u b);

// Multiplication Functions
SNOW_API int
snow_vec2i_dot(snow_vec2i a, snow_vec2i b);
SNOW_API float
snow_vec2f_dot(snow_vec2f a, snow_vec2f b);
SNOW_API snow_uint
snow_vec2u_dot(snow_vec2u a, snow_vec2u b);

SNOW_API snow_vec2i
snow_vec2i_cross(snow_vec2i x, snow_vec2i y);
SNOW_API snow_vec2f
snow_vec2f_cross(snow_vec2f x, snow_vec2f y);
SNOW_API snow_vec2u
snow_vec2u_cross(snow_vec2u x, snow_vec2u y);

// Normalize functions
SNOW_API snow_vec2i
snow_vec2i_norm(snow_vec2i v);
SNOW_API snow_vec2f
snow_vec2f_norm(snow_vec2f v);
SNOW_API snow_vec2u
snow_vec2u_norm(snow_vec2u v);

// Vector 3 Functions
typedef struct snow_vec3i
{
  union
  {
    struct
    {
      int x, y, z;
    };
    struct
    {
      snow_vec2i xy;
    };
  };
} snow_vec3i;

typedef struct snow_vec3f
{
  union
  {
    struct
    {
      float x, y, z;
    };
    struct
    {
      snow_vec2f a;
    };
  };
} snow_vec3f;

typedef struct snow_vec3u
{
  union
  {
    struct
    {
      snow_uint x, y, z;
    };
    struct
    {
      snow_vec2u xy;
    };
  };
} snow_vec3u;

// Addition Scalar Functions
SNOW_API snow_vec3i
snow_vec3i_adds(snow_vec3i v, int s);
SNOW_API snow_vec3f
snow_vec3f_adds(snow_vec3f v, float s);
SNOW_API snow_vec3u
snow_vec3u_addu(snow_vec3u v, snow_uint s);

// Subtraction Scalar Functions
SNOW_API snow_vec3i
snow_vec3f_subs(snow_vec3i v, int s);
SNOW_API snow_vec3f
snow_vec3u_subs(snow_vec3f v, float s);
SNOW_API snow_vec3u
snow_vec3i_subs(snow_vec3u v, snow_uint s);

// Multiplication Scalar Functions
SNOW_API snow_vec3i
snow_vec3i_mults(snow_vec3i v, int s);
SNOW_API snow_vec3f
snow_vec3f_mults(snow_vec3f v, float s);
SNOW_API snow_vec3u
snow_vec3u_mults(snow_vec3u v, snow_uint s);

// Divide Scalar Functions
SNOW_API snow_vec3i
snow_vec3i_divs(snow_vec3i v, int s);
SNOW_API snow_vec3f
snow_vec3f_divs(snow_vec3f v, float s);
SNOW_API snow_vec3u
snow_vec3u_divs(snow_vec3u v, snow_uint s);

// Addition Functions
SNOW_API snow_vec3i
snow_vec3i_add(snow_vec3i a, snow_vec3i b);
SNOW_API snow_vec3f
snow_vec3f_add(snow_vec3f a, snow_vec3f b);
SNOW_API snow_vec3u
snow_vec3u_add(snow_vec3u a, snow_vec3u b);

// Subtraction Functions
SNOW_API snow_vec3i
snow_vec3i_sub(snow_vec3i a, snow_vec3i b);
SNOW_API snow_vec3f
snow_vec3f_sub(snow_vec3f a, snow_vec3f b);
SNOW_API snow_vec3u
snow_vec3u_sub(snow_vec3u a, snow_vec3u b);

// Divide Functions
SNOW_API snow_vec3i
snow_vec3i_div(snow_vec3i a, snow_vec3i b);
SNOW_API snow_vec3f
snow_vec3f_div(snow_vec3f a, snow_vec3f b);
SNOW_API snow_vec3u
snow_vec3u_div(snow_vec3u a, snow_vec3u b);

// Multiplication Functions

SNOW_API int
snow_vec3i_dot(snow_vec3i a, snow_vec3i b);
SNOW_API float
snow_vec3f_dot(snow_vec3f a, snow_vec3f b);
SNOW_API snow_uint
snow_vec3u_dot(snow_vec3u a, snow_vec3u b);

SNOW_API snow_vec3i
snow_vec3i_cross(snow_vec3i x, snow_vec3i y);
SNOW_API snow_vec3f
snow_vec3f_cross(snow_vec3f x, snow_vec3f y);
SNOW_API snow_vec3u
snow_vec3u_cross(snow_vec3u x, snow_vec3u y);

// Normalize functions
SNOW_API snow_vec3i
snow_vec3i_norm(snow_vec3i v);
SNOW_API snow_vec3f
snow_vec3f_norm(snow_vec3f v);
SNOW_API snow_vec3u
snow_vec3u_norm(snow_vec3u v);

// Vec4 functions
typedef struct snow_vec4i
{
  union
  {
    struct
    {
      int x, y, z, w;
    };
    struct
    {
      snow_vec2i xy, zw;
    };
    struct
    {
      snow_vec3i xyz;
    };
  };
} snow_vec4i;

typedef struct snow_vec4f
{
  union
  {
    struct
    {
      float x, y, z, w;
    };
    struct
    {
      snow_vec2f xy, zw;
    };
    struct
    {
      snow_vec3f xyz;
    };
  };
} snow_vec4f;

typedef struct snow_vec4u
{
  union
  {
    struct
    {
      snow_uint x, y, z, w;
    };
    struct
    {
      snow_vec2u xy, zw;
    };
    struct
    {
      snow_vec3u xyz;
    };
  };
} snow_vec4u;

// Mat4 functions
typedef struct snow_mat4f
{
  union
  {
    struct
    {
      float mat[4][4];
    };
    struct
    {
      snow_vec3f row1;
      float w1;
      snow_vec3f row2;
      float w2;
      snow_vec3f row3;
      float w3;
      snow_vec3f row4;
      float w4;
    };
    struct
    {
      float _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30,
        _31, _32, _33;
    };
  };
} snow_mat4f;

SNOW_API snow_mat4f
snow_mat4f_mults(snow_mat4f m, float s);
SNOW_API snow_mat4f
snow_mat4f_mult(snow_mat4f m0, snow_mat4f m1);
SNOW_API snow_vec2f
snow_mat4f_mult2fv(snow_mat4f m, snow_vec2f v);
SNOW_API snow_vec3f
snow_mat4f_mult3fv(snow_mat4f m, snow_vec3f v);

SNOW_API snow_mat4f
snow_mat4f_identity();
SNOW_API snow_mat4f
snow_mat4f_translate2fv(snow_mat4f m, snow_vec2f v);
SNOW_API snow_mat4f
snow_mat4f_scale2fv(snow_mat4f m, snow_vec2f v);
SNOW_API snow_mat4f
snow_mat4f_rotate2fv(snow_mat4f m, float angle_in_radians, snow_vec2f axis);
SNOW_API snow_mat4f
snow_mat4f_translate3fv(snow_mat4f m, snow_vec3f v);
SNOW_API snow_mat4f
snow_mat4f_scale3fv(snow_mat4f m, snow_vec3f v);
SNOW_API snow_mat4f
snow_mat4f_rotate3fv(snow_mat4f m, float angle_in_radians, snow_vec3f axis);

SNOW_API snow_mat4f
snow_mat4f_lookat(snow_vec3f eye, snow_vec3f center, snow_vec3f up);

SNOW_API snow_mat4f
snow_mat4f_prespective(float fovy, float apsect, float znear, float zfar);
SNOW_API snow_mat4f
snow_mat4f_ortho(float left,
                 float right,
                 float bottom,
                 float top,
                 float zNear,
                 float zFar);
SNOW_API snow_mat4f
snow_mat4f_frustum(float left,
                   float right,
                   float bottom,
                   float top,
                   float zNear,
                   float zFar);

// Rectangles
typedef struct snow_recti
{
  int x, y, w, h;
} snow_recti;

typedef struct snow_rectf
{
  float x, y, w, h;
} snow_rectf;

// Colors
typedef struct snow_color
{
  snow_ubyte r, g, b, a;
} snow_color;

// Images
typedef struct snow_image
{
  snow_ubyte* pixels;
  int width;
  int height;
  int number_of_color_channel;
} snow_image;

SNOW_API snow_image*
snow_image_load(snow_char* file);
SNOW_API snow_image*
snow_image_load_from_memory(snow_ubyte* buffer, snow_uint size);
SNOW_API snow_image*
snow_image_clone(snow_image* img);
SNOW_API void
snow_image_free(snow_image** img);

// Textures
SNOW_API snow_texture2d*
snow_texture_create_from_pixels(snow_ubyte* pixels,
                                snow_uint length,
                                int w,
                                int h);
SNOW_API snow_texture2d*
snow_texture_create_from_image(snow_image* img);
SNOW_API snow_texture2d*
snow_texture_clone(snow_texture2d* img);
SNOW_API snow_image*
snow_texture_image_get(snow_texture2d* tex);
SNOW_API void
snow_texture_destroy(snow_texture2d** snow_texture2d);

// Rectangle Shapes
SNOW_API snow_rectangleshape*
snow_rectangleshape_create(int x, int y, int w, int h);
SNOW_API snow_rectangleshape*
snow_rectangleshape_createa(int x, int y, int w, int h, snow_texture2d* tex);
SNOW_API snow_rectangleshape*
snow_rectangleshape_createv(snow_vec2i pos,
                            snow_vec2i dimensions,
                            snow_texture2d* text);
SNOW_API void
snow_rectangleshape_destroy(snow_rectangleshape** rects);
SNOW_API void
snow_rectangleshape_fillcolor_set(snow_rectangleshape* rects,
                                  int r,
                                  int g,
                                  int b,
                                  int a);
SNOW_API void
snow_rectangleshape_texture_set(snow_rectangleshape* shape,
                                snow_texture2d* tex);
SNOW_API snow_rectangleshape*
snow_rectangleshape_clone(snow_rectangleshape* shape);

#endif // SNOW_H
