/*
 * cog.h
 * A lightweight single-header graphics library for development.
 *
 * Provides a straightforward API for window creation, OpenGL context management,
 * texture handling, and hardware-accelerated batch rendering.
 *
 * Usage:
 *   #define COG_IMPLEMENTATION
 *   #include "cog.h"
 *
 * Version: 0.0.1 (Under development)
 * Author: ImJotaM
 * Copyright (c) 2026
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 *
 */

#ifndef COG_H
#define COG_H

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    float x;
    float y;
} cog_vec2;

typedef struct {
    float x;
    float y;
    float width;
    float height;
} cog_rect;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} cog_color;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} cog_colorf;

typedef struct {
    unsigned int id;
    int width;
    int height;
    int channels;
} cog_texture;

typedef struct cog_font cog_font;

typedef struct cog_window cog_window;

typedef enum {
    COG_KEY_UNKNOWN = 0,

    // Numbers
    COG_KEY_0 = 48,
    COG_KEY_1 = 49,
    COG_KEY_2 = 50,
    COG_KEY_3 = 51,
    COG_KEY_4 = 52,
    COG_KEY_5 = 53,
    COG_KEY_6 = 54,
    COG_KEY_7 = 55,
    COG_KEY_8 = 56,
    COG_KEY_9 = 57,

    // Alphabet
    COG_KEY_A = 65,
    COG_KEY_B = 66,
    COG_KEY_C = 67,
    COG_KEY_D = 68,
    COG_KEY_E = 69,
    COG_KEY_F = 70,
    COG_KEY_G = 71,
    COG_KEY_H = 72,
    COG_KEY_I = 73,
    COG_KEY_J = 74,
    COG_KEY_K = 75,
    COG_KEY_L = 76,
    COG_KEY_M = 77,
    COG_KEY_N = 78,
    COG_KEY_O = 79,
    COG_KEY_P = 80,
    COG_KEY_Q = 81,
    COG_KEY_R = 82,
    COG_KEY_S = 83,
    COG_KEY_T = 84,
    COG_KEY_U = 85,
    COG_KEY_V = 86,
    COG_KEY_W = 87,
    COG_KEY_X = 88,
    COG_KEY_Y = 89,
    COG_KEY_Z = 90,

    // System Control Keys
    COG_KEY_BACKSPACE = 8, 
    COG_KEY_TAB       = 9, 
    COG_KEY_ENTER     = 13,
    COG_KEY_ESCAPE    = 27,
    COG_KEY_SPACE     = 32,

    // Navigation Keys
    COG_KEY_PAGEUP    = 33,
    COG_KEY_PAGEDOWN  = 34,
    COG_KEY_END       = 35,
    COG_KEY_HOME      = 36,
    COG_KEY_LEFT      = 37,
    COG_KEY_UP        = 38,
    COG_KEY_RIGHT     = 39,
    COG_KEY_DOWN      = 40,
    COG_KEY_INSERT    = 45,
    COG_KEY_DELETE    = 46,

    // Function Keys
    COG_KEY_F1        = 112,
    COG_KEY_F2        = 113,
    COG_KEY_F3        = 114,
    COG_KEY_F4        = 115,
    COG_KEY_F5        = 116,
    COG_KEY_F6        = 117,
    COG_KEY_F7        = 118,
    COG_KEY_F8        = 119,
    COG_KEY_F9        = 120,
    COG_KEY_F10       = 121,
    COG_KEY_F11       = 122,
    COG_KEY_F12       = 123,

    // Modifiers (Generic/Virtual mapping)
    COG_KEY_SHIFT     = 16,
    COG_KEY_CTRL      = 17,
    COG_KEY_ALT       = 18,
    COG_KEY_CAPSLOCK  = 20,

} cog_key;

typedef enum {

    COG_MOUSE_BUTTON_LEFT = 0,
    COG_MOUSE_BUTTON_RIGHT = 1,
    COG_MOUSE_BUTTON_MIDDLE = 2,

} cog_mouse_button;

cog_window* cog_create_window(const char *title, int width, int height);
void cog_destroy_window(cog_window *window);
bool cog_window_should_close(cog_window *window);

void cog_set_vsync(cog_window* window, bool enabled);
void cog_set_target_fps(cog_window* window, int fps);

int cog_get_window_width(cog_window* window);
int cog_get_window_height(cog_window* window);
cog_vec2 cog_get_window_size(cog_window* window);

float cog_get_delta_time(cog_window* window);
float cog_get_fps(cog_window* window);

void cog_poll_events();

bool cog_is_window_resized(cog_window* window);

bool cog_is_key_pressed(cog_window* window, cog_key key);
bool cog_is_key_pressed_repeat(cog_window* window, cog_key key);
bool cog_is_key_released(cog_window* window, cog_key key);
bool cog_is_key_up(cog_window* window, cog_key key);

cog_vec2 cog_get_mouse_position(cog_window* window);
bool cog_is_mouse_button_pressed(cog_window* window, cog_mouse_button mouse_button);
bool cog_is_mouse_button_down(cog_window* window, cog_mouse_button mouse_button);
bool cog_is_mouse_button_released(cog_window* window, cog_mouse_button mouse_button);
bool cog_is_mouse_button_up(cog_window* window, cog_mouse_button mouse_button);

cog_texture* cog_load_texture(const char* filepath);
void cog_destroy_texture(cog_texture* texture);

cog_font* cog_load_font(const char* filepath);
void cog_destroy_font(cog_font* font);

void cog_clear_background(cog_color color);

void cog_set_rotation(cog_window* window, float rotation);
void cog_set_rotation_origin(cog_window* window, float rotation, cog_vec2 origin);
void cog_reset_rotation(cog_window* window);

void cog_draw_line(cog_window* window, float x1, float y1, float x2, float y2, float thickness, cog_color color);
void cog_draw_rectangle(cog_window* window, float x, float y, int width, int height, cog_color color);
void cog_draw_rectangle_lines(cog_window* window, float x, float y, int width, int height, float thickness, cog_color color);
void cog_draw_triangle(cog_window* window, cog_vec2 p1, cog_vec2 p2, cog_vec2 p3, cog_color color);
void cog_draw_triangle_lines(cog_window* window, cog_vec2 p1, cog_vec2 p2, cog_vec2 p3, float thickness, cog_color color);
void cog_draw_circle(cog_window* window, float x, float y, float radius, int segments, cog_color color);
void cog_draw_circle_lines(cog_window* window, float x, float y, float radius, float thickness, int segments, cog_color color);

void cog_draw_texture(cog_window* window, cog_texture* texture, float x, float y, float width, float height, cog_color color);

void cog_draw_text(cog_window* window, cog_font* font, const char* text, float x, float y, float fontsize, cog_color color);

void cog_render(cog_window *window);

/**
 * Color conversion functions
 * 
 * @note All hex values use RGBA channel order:
 *       - Bits 31-24: Red channel
 *       - Bits 23-16: Green channel
 *       - Bits 15-8:  Blue channel
 *       - Bits 7-0:   Alpha channel
 *       Example: 0xFF8000FF = Red:255, Green:128, Blue:0, Alpha:255
 * 
 * @note Float values are expected in range [0.0, 1.0]
 * @note Unsigned char values are expected in range [0, 255]
 * 
 **/

cog_color cog_rgba_to_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
cog_color cog_rgbaf_to_color(float r, float g, float b, float a);
cog_color cog_colorf_to_color(cog_colorf colorf);
cog_color cog_hex_to_color(uint32_t hex_color);

cog_colorf cog_rgba_to_colorf(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
cog_colorf cog_rgbaf_to_colorf(float r, float g, float b, float a);
cog_colorf cog_color_to_colorf(cog_color color);
cog_colorf cog_hex_to_colorf(uint32_t hex_color);

uint32_t cog_rgba_to_hex(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
uint32_t cog_rgbaf_to_hex(float r, float g, float b, float a);
uint32_t cog_color_to_hex(cog_color color);
uint32_t cog_colorf_to_hex(cog_colorf colorf);

bool cog_is_point_in_rect(cog_vec2 point, cog_rect rect);

cog_vec2 cog_measure_text(cog_font* font, const char* text, float fontsize);

#endif // COG_H


#ifdef COG_IMPLEMENTATION

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

#include <GL/gl.h>

#define COG_PACK_KEY(key, state) (((uint32_t)(state) << 30) | ((uint32_t)(key)))
#define COG_GET_KEY(packed) ((packed) & 0x3fffffff)
#define COG_GET_STATE(packed) ((packed) >> 30)

typedef struct {
    float x, y, z;
    float r, g, b, a;
    float u, v;
} cog_vertex;

typedef struct {
    unsigned int texture_id;
    size_t vertex_start;
    size_t vertex_count;
} cog_batch;

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int program;

    int loc_resolution;
    int loc_use_texture;

    cog_vertex* vertices;
    size_t vertex_count;
    size_t vertex_capacity;

    cog_batch* batches;
    size_t batch_count;
    size_t batch_capacity;

    float rotation;
    cog_vec2 rotation_origin;
    cog_vec2 auto_origin;
    float cos_rot;
    float sin_rot;
} cog_renderer;

typedef enum {
    
    COG_EVENT_NONE = 0,

    COG_EVENT_WINDOW_RESIZE = 1,

    COG_EVENT_KEY_UP = 0,
    COG_EVENT_KEY_PRESSED = 1,
    COG_EVENT_KEY_PRESSED_REPEAT = 2,
    COG_EVENT_KEY_RELEASED = 3,

    COG_EVENT_MOUSE_PRESSED = 1,
    COG_EVENT_MOUSE_RELEASED = 2,

} cog_event_type;

typedef struct {
    cog_event_type type;
} cog_event_window;

typedef struct {
    uint32_t key_buffer[512];
} cog_event_key;

typedef struct {
    int x;
    int y;
    bool mouse_held[3];
    uint8_t mouse_buffer[3];
} cog_event_mouse;

typedef struct {
    cog_event_window window;
    cog_event_key key;
    cog_event_mouse mouse;
} cog_events;

struct cog_window {
    HWND handle;
    HDC device_context;
    HGLRC rendering_context;
    int width;
    int height;
    bool should_close;
    int target_fps;
    LARGE_INTEGER timer_frequency;
    LARGE_INTEGER last_frame_time;
    float delta_time;
    cog_events events;
    cog_renderer* renderer;
};

typedef struct {
    uint32_t codepoint;
    float u0, v0, u1, v1;
    float x0, y0, x1, y1;
    float x_offset;
} cog_glyph;

struct cog_font {
    cog_texture* texture;
    float size;
    float scale;
    stbtt_fontinfo info;
    unsigned char* raw_data;

    cog_glyph* glyphs;
    size_t glyph_count;
    size_t glyph_capacity;

    int atlas_cursor_x;
    int atlas_cursor_y;
    int max_row_height;
};

#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER   0x8B31
#define GL_COMPILE_STATUS  0x8B81
#define GL_LINK_STATUS     0x8B82

#define GL_ARRAY_BUFFER 0x8892
#define GL_DYNAMIC_DRAW 0x88E8

#define GL_CLAMP_TO_EDGE 0x812f

#define GL_FUNCTIONS \
    X(void,         glGenVertexArrays,         "glGenVertexArrays",         (int n, unsigned int* arrays)) \
    X(void,         glBindVertexArray,         "glBindVertexArray",         (unsigned int array)) \
    X(void,         glGenBuffers,              "glGenBuffers",              (int n, unsigned int* buffers)) \
    X(void,         glBindBuffer,              "glBindBuffer",              (unsigned int target, unsigned int buffer)) \
    X(void,         glBufferData,              "glBufferData",              (unsigned int target, ptrdiff_t size, const void* data, unsigned int usage)) \
    X(void,         glVertexAttribPointer,     "glVertexAttribPointer",     (unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void *pointer)) \
    X(void,         glEnableVertexAttribArray, "glEnableVertexAttribArray", (unsigned int index)) \
    X(unsigned int, glCreateShader,            "glCreateShader",            (unsigned int type)) \
    X(void,         glShaderSource,            "glShaderSource",            (unsigned int shader, int count, const char** string, const int* length)) \
    X(void,         glCompileShader,           "glCompileShader",           (unsigned int shader)) \
    X(void,         glGetShaderiv,             "glGetShaderiv",             (unsigned int shader, unsigned int pname, int* params)) \
    X(void,         glGetShaderInfoLog,        "glGetShaderInfoLog",        (unsigned int shader, int bufSize, int* length, char *infoLog)) \
    X(unsigned int, glCreateProgram,           "glCreateProgram",           (void)) \
    X(void,         glAttachShader,            "glAttachShader",            (unsigned int program, unsigned int shader)) \
    X(void,         glLinkProgram,             "glLinkProgram",             (unsigned int program)) \
    X(void,         glUseProgram,              "glUseProgram",              (unsigned int program)) \
    X(void,         glGetProgramiv,            "glGetProgramiv",            (unsigned int program, unsigned int pname, int* params)) \
    X(void,         glGetProgramInfoLog,       "glGetProgramInfoLog",       (unsigned int program, int bufSize, int* length, char* infoLog)) \
    X(void,         glDeleteShader,            "glDeleteShader",            (unsigned int shader)) \
    X(void,         glBufferSubData,           "glBufferSubData",           (unsigned int target, ptrdiff_t offset, ptrdiff_t size, const void *data)) \
    X(void,         glUniform1i,               "glUniform1i",               (int location, int v0)) \
    X(void,         glUniform2f,               "glUniform2f",               (int location, float v0, float v1)) \
    X(int,          glGetUniformLocation,      "glGetUniformLocation",      (int program, const char* name)) \
    X(void,         glDeleteVertexArrays,      "glDeleteVertexArrays",      (long n, const unsigned int* arrays)) \
    X(void,         glDeleteBuffers,           "glDeleteBuffers",           (long n, const unsigned int* buffers)) \
    X(void,         glDeleteProgram,           "glDeleteProgram",           (unsigned int program)) \
    X(void,         glGenerateMipmap,          "glGenerateMipmap",          (unsigned int target))

#define X(ret, name, str, args) static ret (APIENTRY *name) args = NULL;
GL_FUNCTIONS
#undef X

typedef BOOL (WINAPI *wglSwapIntervalEXT_func)(int interval);
static wglSwapIntervalEXT_func wglSwapIntervalEXT = NULL;

static void* _cog_load_gl_function(const char *name) {
    void *func = (void*)wglGetProcAddress(name);
    if (!func) {
        HMODULE module = GetModuleHandleA("opengl32.dll");
        if (module) {
            func = (void*)GetProcAddress(module, name);
        }
    }
    return func;
}

static int _cog_init_gl_functions(void) {
    int success = true;

    #define X(ret, name, str, args) \
        name = (ret (APIENTRY *) args)_cog_load_gl_function(str); \
        if (!name) success = false;
    
    GL_FUNCTIONS
    #undef X

    wglSwapIntervalEXT = (wglSwapIntervalEXT_func)wglGetProcAddress("wglSwapIntervalEXT");

    return success;
}

static const char* vertex_shader_src = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"uniform vec2 u_resolution;\n"
"out vec4 ourColor;\n"
"out vec2 TexCoord;\n"
"void main() {\n"
"    vec2 zeroToOne = aPos.xy / u_resolution;\n"
"    vec2 zeroToTwo = zeroToOne * 2.0;\n"
"    vec2 clipSpace = zeroToTwo - 1.0;\n"
"    gl_Position = vec4(clipSpace * vec2(1.0, -1.0), aPos.z, 1.0);\n"
"    ourColor = aColor;\n"
"    TexCoord = aTexCoord;\n"
"}\n"
;

static const char* fragment_shader_src = 
"#version 330 core\n"
"in vec4 ourColor;\n"
"in vec2 TexCoord;\n"
"out vec4 FragColor;\n"
"uniform sampler2D u_texture;\n"
"uniform int u_use_texture;\n"
"void main() {\n"
"    if (u_use_texture > 0) {\n"
"        FragColor = texture(u_texture, TexCoord) * ourColor;\n"
"    } else {\n"
"        FragColor = ourColor;\n"
"    }\n"
"}\n"
;

static unsigned int _cog_compile_shader(const char* vertex_shader_src, const char* fragment_shader_src) {

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        printf("Error: Shader compilation failed: %s\n", infoLog);
    }
    
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment_shader);
    
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        printf("Error: Shader compilation failed: %s\n", infoLog);
    }
    
    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        printf("Error: Shader compilation failed: %s\n", infoLog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}

static cog_renderer* _cog_create_renderer() {
    cog_renderer* renderer = (cog_renderer*)malloc(sizeof(cog_renderer));
    renderer->program = _cog_compile_shader(vertex_shader_src, fragment_shader_src);

    renderer->loc_resolution = glGetUniformLocation(renderer->program, "u_resolution");
    renderer->loc_use_texture = glGetUniformLocation(renderer->program, "u_use_texture");

    glGenVertexArrays(1, &renderer->VAO);
    glGenBuffers(1, &renderer->VBO);

    glBindVertexArray(renderer->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->VBO);

    // Position (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cog_vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Color (Location 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(cog_vertex), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    // Texture Coordinates (Location 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(cog_vertex), (void*)(sizeof(float) * 7));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    renderer->vertex_capacity = 1024;
    renderer->vertex_count = 0;
    renderer->vertices = (cog_vertex*)malloc(sizeof(cog_vertex) * renderer->vertex_capacity);
    
    renderer->batch_capacity = 64;
    renderer->batch_count = 0;
    renderer->batches = (cog_batch*)malloc(sizeof(cog_batch) * renderer->batch_capacity);

    renderer->rotation = 0.0f;
    renderer->rotation_origin = (cog_vec2){ -1.0f, -1.0f };
    renderer->auto_origin = (cog_vec2){ 0.0f, 0.0f };
    renderer->cos_rot = 1.0f;
    renderer->sin_rot = 0.0f;

    return renderer;
}

static void _cog_push_vertex(cog_renderer* renderer, cog_vertex v) {
    if (renderer->rotation != 0.0f) {
        cog_vec2 pivot = renderer->rotation_origin;
        if (pivot.x == -1.0f && pivot.y == -1.0f) {
            pivot = renderer->auto_origin;
        }
        float dx = v.x - pivot.x;
        float dy = v.y - pivot.y;
        v.x = pivot.x + (dx * renderer->cos_rot - dy * renderer->sin_rot);
        v.y = pivot.y + (dx * renderer->sin_rot + dy * renderer->cos_rot);
    }
    if (renderer->vertex_count >= renderer->vertex_capacity) {
        renderer->vertex_capacity *= 2;
        renderer->vertices = (cog_vertex*)realloc(renderer->vertices, sizeof(cog_vertex) * renderer->vertex_capacity);
    }
    renderer->vertices[renderer->vertex_count++] = v;
}

static cog_batch* _cog_get_batch(cog_renderer* renderer, unsigned int texture_id) {
    if (renderer->batch_count > 0) {
        cog_batch* last_batch = &renderer->batches[renderer->batch_count - 1];
        if (last_batch->texture_id == texture_id) {
            return last_batch;
        }
    }

    if (renderer->batch_count >= renderer->batch_capacity) {
        renderer->batch_capacity *= 2;
        renderer->batches = (cog_batch*)realloc(renderer->batches, sizeof(cog_batch) * renderer->batch_capacity);
    }

    cog_batch* batch = &renderer->batches[renderer->batch_count++];
    batch->texture_id = texture_id;
    batch->vertex_start = renderer->vertex_count;
    batch->vertex_count = 0;

    return batch;
}

static LRESULT CALLBACK _cog_window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    cog_window *window = NULL;
    
    if (msg == WM_CREATE) {
        CREATESTRUCT *create_struct = (CREATESTRUCT*)lParam;
        window = (cog_window*)create_struct->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
    } else {
        window = (cog_window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
    
    if (!window) return DefWindowProc(hwnd, msg, wParam, lParam);

    switch (msg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            window->should_close = true;
            PostQuitMessage(0);
            return 0;
        }
        case WM_SIZE: {
            window->width = LOWORD(lParam);
            window->height = HIWORD(lParam);
            window->events.window.type |= COG_EVENT_WINDOW_RESIZE;
            
            if (window->rendering_context) {
                glViewport(0, 0, window->width, window->height);
            }
            return 0;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {

            WORD vk_code = LOWORD(wParam);
            WORD key_flags = HIWORD(lParam);
            
            cog_event_type state = COG_KEY_UP;
            if (msg == WM_KEYUP || msg == WM_SYSKEYUP) {
                state = COG_EVENT_KEY_RELEASED;
            } else {
                bool was_key_down = (key_flags & KF_REPEAT) == KF_REPEAT;
                if (was_key_down) {
                    state = COG_EVENT_KEY_PRESSED_REPEAT;
                } else {
                    state = COG_EVENT_KEY_PRESSED;
                }
            }

            window->events.key.key_buffer[vk_code] = COG_PACK_KEY(vk_code, state);
            return 0;
        }
        case WM_MOUSEMOVE: {
            window->events.mouse.x = GET_X_LPARAM(lParam);
            window->events.mouse.y = GET_Y_LPARAM(lParam);
            return 0;
        }
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN: {
            
            window->events.mouse.x = GET_X_LPARAM(lParam);
            window->events.mouse.y = GET_Y_LPARAM(lParam);
            
            cog_mouse_button mouse_button;
            if      (msg == WM_LBUTTONDOWN) mouse_button = COG_MOUSE_BUTTON_LEFT;
            else if (msg == WM_RBUTTONDOWN) mouse_button = COG_MOUSE_BUTTON_RIGHT;
            else if (msg == WM_MBUTTONDOWN) mouse_button = COG_MOUSE_BUTTON_MIDDLE;
            
            window->events.mouse.mouse_buffer[mouse_button] = COG_EVENT_MOUSE_PRESSED;
            window->events.mouse.mouse_held[mouse_button] = true;

            return 0;
        }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP: {

            window->events.mouse.x = GET_X_LPARAM(lParam);
            window->events.mouse.y = GET_Y_LPARAM(lParam);
            
            cog_mouse_button mouse_button;
            if      (msg == WM_LBUTTONUP) mouse_button = COG_MOUSE_BUTTON_LEFT;
            else if (msg == WM_RBUTTONUP) mouse_button = COG_MOUSE_BUTTON_RIGHT;
            else if (msg == WM_MBUTTONUP) mouse_button = COG_MOUSE_BUTTON_MIDDLE;
            
            window->events.mouse.mouse_buffer[mouse_button] = COG_EVENT_MOUSE_RELEASED;
            window->events.mouse.mouse_held[mouse_button] = false;

            return 0;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

static void _cog_reset_window(cog_window* window) {
    window->events.window.type = 0;
    memset(window->events.key.key_buffer, 0, sizeof(window->events.key.key_buffer));
    memset(window->events.mouse.mouse_buffer, 0, sizeof(window->events.mouse.mouse_buffer));
}

static unsigned int _cog_load_texture_data(unsigned char* data, int width, int height, int channels) {
    unsigned int texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    GLenum format;
    if (channels == 1) format = GL_RED;
    else if (channels == 3) format = GL_RGB;
    else if (channels == 4) format = GL_RGBA;
    else format = GL_RGBA;
    
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    return texture_id;
}

static uint32_t _cog_utf8_decode(const char** text) {
    const unsigned char* s = (const unsigned char*)(*text);
    if (!s || !*s) return 0;

    uint32_t cp = 0;
    if (*s < 0x80) {
        cp = *s;
        *text += 1;
    } else if ((*s & 0xE0) == 0xC0) {
        cp = ((*s & 0x1F) << 6) | (s[1] & 0x3F);
        *text += 2;
    } else if ((*s & 0xF0) == 0xE0) {
        cp = ((*s & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
        *text += 3;
    } else if ((*s & 0xF8) == 0xF0) {
        cp = ((*s & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] &0x3F);
        *text += 4;
    } else {
        *text += 1;
    }
    return cp;
}

static cog_glyph* _cog_get_or_load_glyph(cog_font* font, uint32_t codepoint) {
    for (size_t i = 0; i < font->glyph_count; i++) {
        if (font->glyphs[i].codepoint == codepoint) {
            return &font->glyphs[i];
        }
    }

    int glyph_index = stbtt_FindGlyphIndex(&font->info, (int)codepoint);
    if (glyph_index == 0 && codepoint != ' ') {
        // Glyph not supported by font
        return NULL;
    }

    int advance_width, left_side_bearing;
    stbtt_GetCodepointHMetrics(&font->info, (int)codepoint, &advance_width, &left_side_bearing);

    int ix0, iy0, ix1, iy1;
    stbtt_GetCodepointBitmapBox(&font->info, (int)codepoint, font->scale, font->scale, &ix0, &iy0, &ix1, &iy1);

    int gw = ix1 - ix0;
    int gh = iy1 - iy0;

    if (font->atlas_cursor_x + gw + 1 >= font->texture->width) {
        font->atlas_cursor_y += font->max_row_height + 1;
        font->atlas_cursor_x = 1;
        font->max_row_height = 0;
    }

    if (font->atlas_cursor_y + gh + 1 >= font->texture->height) {
        fprintf(stderr, "Warning: Font atlas texture is full\n");
        return NULL;
    }

    if (gh > font->max_row_height) {
        font->max_row_height = gh;
    }

    int px = font->atlas_cursor_x;
    int py = font->atlas_cursor_y;

    if (gw > 0 && gh > 0) {
        unsigned char* mono_bitmap = (unsigned char*)calloc(gw * gh, 1);
        stbtt_MakeCodepointBitmap(&font->info, mono_bitmap, gw, gh, gw, font->scale, font->scale, (int)codepoint);

        unsigned char* rgba_bitmap = (unsigned char*)malloc(gw * gh * 4);
        for (int i = 0; i < gw * gh; i++) {
            rgba_bitmap[i * 4 + 0] = 255;
            rgba_bitmap[i * 4 + 1] = 255;
            rgba_bitmap[i * 4 + 2] = 255;
            rgba_bitmap[i * 4 + 3] = mono_bitmap[i];
        }

        glBindTexture(GL_TEXTURE_2D, font->texture->id);
        glTexSubImage2D(GL_TEXTURE_2D, 0, px, py, gw, gh, GL_RGBA, GL_UNSIGNED_BYTE, rgba_bitmap);
        glBindTexture(GL_TEXTURE_2D, 0);

        free(mono_bitmap);
        free(rgba_bitmap);
    }

    font->atlas_cursor_x += gw + 1;

    if (font->glyph_count >= font->glyph_capacity) {
        font->glyph_capacity *= 2;
        font->glyphs = (cog_glyph*)realloc(font->glyphs, sizeof(cog_glyph) * font->glyph_capacity);
    }

    cog_glyph* g = &font->glyphs[font->glyph_count++];
    g->codepoint = codepoint;
    g->u0 = (float)px / (float)font->texture->width;
    g->v0 = (float)py / (float)font->texture->height;
    g->u1 = (float)(px + gw) / (float)font->texture->width;
    g->v1 = (float)(py + gh) / (float)font->texture->height;
    g->x0 = (float)ix0;
    g->y0 = (float)iy0;
    g->x1 = (float)ix1;
    g->y1 = (float)iy1;
    g->x_offset = (float)advance_width * font->scale;

    return g;
}

cog_window* cog_create_window(const char *title, int width, int height) {
    cog_window *window = (cog_window*)malloc(sizeof(cog_window));
    if (!window) return NULL;
    
    memset(window, 0, sizeof(cog_window));
    window->width = width;
    window->height = height;
    window->should_close = false;
    
    HINSTANCE instance = GetModuleHandle(NULL);
    
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = _cog_window_proc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "CogWindowClass";
    wc.style = CS_OWNDC;
    
    RegisterClassA(&wc);
    
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    
    window->handle = CreateWindowA(
        "CogWindowClass",
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL, NULL,
        instance,
        window
    );

    if (!window->handle) {
        free(window);
        return NULL;
    }
    
    window->device_context = GetDC(window->handle);
    if (!window->device_context) {
        DestroyWindow(window->handle);
        free(window);
        return NULL;
    }
    
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0, 0,
        0, 0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    
    int pixel_format = ChoosePixelFormat(window->device_context, &pfd);
    SetPixelFormat(window->device_context, pixel_format, &pfd);
    
    HGLRC temp_context = wglCreateContext(window->device_context);
    if (!temp_context) {
        ReleaseDC(window->handle, window->device_context);
        DestroyWindow(window->handle);
        free(window);
        return NULL;
    }
    
    wglMakeCurrent(window->device_context, temp_context);
    
    typedef HGLRC (WINAPI *wgl_create_context_attribs_arb_func)(HDC, HGLRC, const int*);
    wgl_create_context_attribs_arb_func wglCreateContextAttribsARB = (wgl_create_context_attribs_arb_func)wglGetProcAddress("wglCreateContextAttribsARB");
    
    const int WGL_CONTEXT_MAJOR_VERSION_ARB = 0x2091;
    const int WGL_CONTEXT_MINOR_VERSION_ARB = 0x2092;
    const int WGL_CONTEXT_FLAGS_ARB         = 0x2094;

    if (wglCreateContextAttribsARB) {
        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
            WGL_CONTEXT_MINOR_VERSION_ARB, 3,
            WGL_CONTEXT_FLAGS_ARB, 0,
            0
        };
        
        window->rendering_context = wglCreateContextAttribsARB(window->device_context, 0, attribs);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(temp_context);
        wglMakeCurrent(window->device_context, window->rendering_context);
    } else {
        window->rendering_context = temp_context;
    }
    
    if (!_cog_init_gl_functions()) {
        cog_destroy_window(window);
        return NULL;
    }
    
    ShowWindow(window->handle, SW_SHOW);
    UpdateWindow(window->handle);
    
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
    
    window->renderer = _cog_create_renderer();
    
    QueryPerformanceFrequency(&window->timer_frequency);
    QueryPerformanceCounter(&window->last_frame_time);
    window->target_fps = 0;
    window->delta_time = 0.0f;

    HMODULE winmm = LoadLibraryA("winmm.dll");
    if (winmm) {
        typedef UINT (WINAPI *timeBeginPeriod_t)(UINT);
        timeBeginPeriod_t p_timeBeginPeriod = (timeBeginPeriod_t)GetProcAddress(winmm, "timeBeginPeriod");
        if (p_timeBeginPeriod) p_timeBeginPeriod(1);
    }

    return window;
}

void cog_destroy_window(cog_window *window) {
    if (!window) return;
    
    if (window->renderer) {
        glDeleteVertexArrays(1, &window->renderer->VAO);
        glDeleteBuffers(1, &window->renderer->VAO);
        glDeleteProgram(window->renderer->program);
        free(window->renderer->vertices);
        free(window->renderer->batches);
        free(window->renderer);
    }

    if (window->rendering_context) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(window->rendering_context);
    }
    
    if (window->device_context) {
        ReleaseDC(window->handle, window->device_context);
    }
    
    if (window->handle) {
        DestroyWindow(window->handle);
    }
    
    HMODULE winmm = GetModuleHandleA("winmm.dll");
    if (winmm) {
        typedef UINT (WINAPI *timeEndPeriod_t)(UINT);
        timeEndPeriod_t p_timeEndPeriod = (timeEndPeriod_t)GetProcAddress(winmm, "timeEndPeriod");
        if (p_timeEndPeriod) p_timeEndPeriod(1);
    }

    free(window);
}

bool cog_window_should_close(cog_window *window) {
    return window ? window->should_close : true;
}

void cog_set_vsync(cog_window* window, bool enabled) {
    (void)window;
    if (wglSwapIntervalEXT) {
        wglSwapIntervalEXT(enabled ? 1 : 0);
    }
}

void cog_set_target_fps(cog_window* window, int fps) {
    if (!window) return;
    window->target_fps = fps > 0 ? fps : 0;
}

int cog_get_window_width(cog_window* window) {
    return window->width;
}

int cog_get_window_height(cog_window* window) {
    return window->height;
}

cog_vec2 cog_get_window_size(cog_window* window) {
    return (cog_vec2){ window->width, window->height };
}

float cog_get_delta_time(cog_window* window) {
    return window ? window->delta_time : 0.0f;
}

float cog_get_fps(cog_window* window) {
    if (!window || window->delta_time <= 0.0f) return 0.0f;
    return 1.0f / window->delta_time;
}

void cog_poll_events() {
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

bool cog_is_window_resized(cog_window* window) {
    if (!window) return false;
    return (window->events.window.type & COG_EVENT_WINDOW_RESIZE) == COG_EVENT_WINDOW_RESIZE;
}

bool cog_is_key_pressed(cog_window* window, cog_key key) {
    if (!window) return false;
    return COG_GET_STATE(window->events.key.key_buffer[key]) == COG_EVENT_KEY_PRESSED;
}

bool cog_is_key_pressed_repeat(cog_window* window, cog_key key) {
    if (!window) return false;
    return COG_GET_STATE(window->events.key.key_buffer[key]) == COG_EVENT_KEY_PRESSED_REPEAT;
}

bool cog_is_key_released(cog_window* window, cog_key key) {
    if (!window) return false;
    return COG_GET_STATE(window->events.key.key_buffer[key]) == COG_EVENT_KEY_RELEASED;
}

bool cog_is_key_up(cog_window* window, cog_key key) {
    if (!window) return false;
    return COG_GET_STATE(window->events.key.key_buffer[key]) == COG_EVENT_KEY_UP;
}

cog_vec2 cog_get_mouse_position(cog_window* window) {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(window->handle, &p);

    cog_vec2 pos;
    pos.x = (float)p.x;
    pos.y = (float)p.y;
    return pos;
}

bool cog_is_mouse_button_pressed(cog_window* window, cog_mouse_button mouse_button) {
    return window->events.mouse.mouse_buffer[mouse_button] == COG_EVENT_MOUSE_PRESSED;
}

bool cog_is_mouse_button_down(cog_window* window, cog_mouse_button mouse_button) {
    return window->events.mouse.mouse_held[mouse_button] == true;
}

bool cog_is_mouse_button_released(cog_window* window, cog_mouse_button mouse_button) {
    return window->events.mouse.mouse_buffer[mouse_button] == COG_EVENT_MOUSE_RELEASED;
}

bool cog_is_mouse_button_up(cog_window* window, cog_mouse_button mouse_button) {
    return window->events.mouse.mouse_held[mouse_button] == false;
}

cog_texture* cog_load_texture(const char* filepath) {

    int width, height;

    unsigned char* data = stbi_load(filepath, &width, &height, NULL, 4);
    if (!data) {
        printf("Error loading texture: %s\n", filepath);
        return NULL;
    }

    cog_texture* texture = (cog_texture*)malloc(sizeof(cog_texture));
    
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    texture->id = id;
    texture->width = width;
    texture->height = height;
    texture->channels = 4;

    return texture;
}

void cog_destroy_texture(cog_texture* texture) {
    if (!texture) return;
    glDeleteTextures(1, &texture->id);
    free(texture);
}

cog_font* cog_load_font(const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    
    if (!file) {
        fprintf(stderr, "Error loading font: %s\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* data = (unsigned char*)malloc(size);
    fread(data, 1, size, file);
    fclose(file);

    cog_font* font = (cog_font*)malloc(sizeof(cog_font));
    font->raw_data = data;
    font->size = 32.0f;

    if (!stbtt_InitFont(&font->info, font->raw_data, 0)) {
        free(font->raw_data);
        free(font);
        return NULL;
    }

    font->scale = stbtt_ScaleForPixelHeight(&font->info, font->size);

    int atlas_width = 2048;
    int atlas_height = 2048;
    unsigned char* blank_atlas = calloc(atlas_width * atlas_height * 4, 1);

    font->texture = (cog_texture*)malloc(sizeof(cog_texture));
    font->texture->id = _cog_load_texture_data(blank_atlas, atlas_width, atlas_height, 4);
    font->texture->width = atlas_width;
    font->texture->height = atlas_height;
    font->texture->channels = 4;
    free(blank_atlas);

    font->glyph_capacity = 128;
    font->glyph_count = 0;
    font->glyphs = (cog_glyph*)malloc(sizeof(cog_glyph) * font->glyph_capacity);

    font->atlas_cursor_x = 1;
    font->atlas_cursor_y = 1;
    font->max_row_height = 0;

    return font;
}

void cog_destroy_font(cog_font* font) {
    if (!font) return;
    if (font->texture) {
        cog_destroy_texture(font->texture);
    }
    if (font->raw_data) {
        free(font->raw_data);
    }
    if (font->glyphs) {
        free(font->glyphs);
    }
    free(font);
}

void cog_clear_background(cog_color color) {
    cog_colorf c = cog_color_to_colorf(color);
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void cog_set_rotation(cog_window* window, float angle) {
    cog_set_rotation_origin(window, angle, (cog_vec2){ -1.0f, -1.0f });
}

void cog_set_rotation_origin(cog_window* window, float rotation, cog_vec2 origin) {
    cog_renderer* r = window->renderer;
    r->rotation = rotation;
    r->rotation_origin = origin;

    if (rotation != 0) {
        float rad = rotation / 180.0f * (float)M_PI;
        r->cos_rot = cosf(rad);
        r->sin_rot = sinf(rad);
    } else {
        r->cos_rot = 1.0f;
        r->sin_rot = 0.0f;
    }
}

void cog_reset_rotation(cog_window* window) {
    cog_set_rotation(window, 0.0f);
}

void cog_draw_line(cog_window* window, float x1, float y1, float x2, float y2, float thickness, cog_color color) {
    
    float nx, ny;

    {
        float dx = x2 - x1;
        float dy = y2 - y1;
        float lenght = sqrtf(dx * dx + dy * dy);
        if (lenght == 0.0f) return;

        nx = (-dy / lenght) * (thickness * 0.5f);
        ny = ( dx / lenght) * (thickness * 0.5f);
    }

    float ax = x1 + nx, ay = y1 + ny;
    float bx = x2 + nx, by = y2 + ny;
    float cx = x1 - nx, cy = y1 - ny;
    float dx = x2 - nx, dy = y2 - ny;

    float z = 0.0f;
    cog_colorf c = cog_color_to_colorf(color);

    cog_renderer* r = window->renderer;
    r->auto_origin = (cog_vec2){ (x1 + x2) * 0.5f, (y1 + y2) * 0.5f };

    cog_batch* batch = _cog_get_batch(r, 0);

    _cog_push_vertex(r, (cog_vertex){ ax, ay, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ bx, by, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ cx, cy, z, c.r, c.g, c.b, c.a });

    _cog_push_vertex(r, (cog_vertex){ bx, by, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ cx, cy, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ dx, dy, z, c.r, c.g, c.b, c.a });

    batch->vertex_count += 6;
}

void cog_draw_rectangle(cog_window* window, float x, float y, int width, int height, cog_color color) {
    float x1 = x;
    float y1 = y;
    float x2 = x + width;
    float y2 = y + height;
    float z  = 0.0f;
    cog_colorf c = cog_color_to_colorf(color);

    cog_renderer* r = window->renderer;
    r->auto_origin = (cog_vec2){ x + width * 0.5f, y + height * 0.5f };

    cog_batch* batch = _cog_get_batch(r, 0);

    _cog_push_vertex(r, (cog_vertex){ x1, y1, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ x2, y1, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ x1, y2, z, c.r, c.g, c.b, c.a });
    
    _cog_push_vertex(r, (cog_vertex){ x1, y2, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ x2, y1, z, c.r, c.g, c.b, c.a });
    _cog_push_vertex(r, (cog_vertex){ x2, y2, z, c.r, c.g, c.b, c.a });

    batch->vertex_count += 6;
}

void cog_draw_rectangle_lines(cog_window* window, float x, float y, int width, int height, float thickness, cog_color color) {
    cog_renderer* r = window->renderer;
    cog_vec2 prev_origin = r->rotation_origin;

    if (r->rotation_origin.x == -1.0f && r->rotation_origin.y == -1.0f) {
        r->rotation_origin = (cog_vec2){ x + width * 0.5f, y + height * 0.5f };
    }

    cog_draw_rectangle(window, x, y, width, thickness, color);
    cog_draw_rectangle(window, x, y + height - thickness, width, thickness, color);
    cog_draw_rectangle(window, x, y + thickness, thickness, height - 2.0f * thickness, color);
    cog_draw_rectangle(window, x + width - thickness, y + thickness, thickness, height - 2.0f * thickness, color);

    r->rotation_origin = prev_origin;
}

void cog_draw_triangle(cog_window* window, cog_vec2 p1, cog_vec2 p2, cog_vec2 p3, cog_color color) {
    float z = 0.0f;
    cog_colorf c = cog_color_to_colorf(color);
    
    cog_renderer* r = window->renderer;
    float min_x = fminf(p1.x, fminf(p2.x, p3.x));
    float max_x = fmaxf(p1.x, fmaxf(p2.x, p3.x));
    float min_y = fminf(p1.y, fminf(p2.y, p3.y));
    float max_y = fmaxf(p1.y, fmaxf(p2.y, p3.y));
    r->auto_origin = (cog_vec2){ (min_x + max_x) * 0.5f, (min_y + max_y) * 0.5f };

    cog_batch* batch = _cog_get_batch(r, 0);

    _cog_push_vertex(r, (cog_vertex){ p1.x, p1.y, z, c.r, c.g, c.b, c.a});
    _cog_push_vertex(r, (cog_vertex){ p2.x, p2.y, z, c.r, c.g, c.b, c.a});
    _cog_push_vertex(r, (cog_vertex){ p3.x, p3.y, z, c.r, c.g, c.b, c.a});

    batch->vertex_count += 3;
}

void cog_draw_triangle_lines(cog_window* window, cog_vec2 p1, cog_vec2 p2, cog_vec2 p3, float thickness, cog_color color) {
    cog_renderer* r = window->renderer;
    cog_vec2 prev_origin = r->rotation_origin;

    if (r->rotation_origin.x == -1.0f && r->rotation_origin.y == -1.0f) {
        float min_x = fminf(p1.x, fminf(p2.x, p3.x));
        float max_x = fmaxf(p1.x, fmaxf(p2.x, p3.x));
        float min_y = fminf(p1.y, fminf(p2.y, p3.y));
        float max_y = fmaxf(p1.y, fmaxf(p2.y, p3.y));
        r->rotation_origin = (cog_vec2){ (min_x + max_x) * 0.5f, (min_y + max_y) * 0.5f };
    }

    cog_draw_line(window, p1.x, p1.y, p2.x, p2.y, thickness, color);
    cog_draw_line(window, p2.x, p2.y, p3.x, p3.y, thickness, color);
    cog_draw_line(window, p3.x, p3.y, p1.x, p1.y, thickness, color);

    r->rotation_origin = prev_origin;
}

void cog_draw_circle(cog_window* window, float x, float y, float radius, int segments, cog_color color) {
    segments = segments ? segments : 36;
    float angle_step = (2.0f * M_PI) / segments;
    float z = 0.0f;
    cog_colorf c = cog_color_to_colorf(color);
    
    cog_renderer* r = window->renderer;
    r->auto_origin = (cog_vec2){ x, y };
    
    cog_batch* batch = _cog_get_batch(r, 0);

    for (int i = 0; i < segments; i++) {
        float theta1 = i * angle_step;
        float theta2 = (i + 1) * angle_step;
        
        _cog_push_vertex(r, (cog_vertex){ x, y, z, c.r, c.g, c.b, c.a });
        
        _cog_push_vertex(r, (cog_vertex){
            x + radius * cosf(theta1), 
            y + radius * sinf(theta1), 
            z, c.r, c.g, c.b, c.a,
        });
        
        _cog_push_vertex(r, (cog_vertex){
            x + radius * cosf(theta2), 
            y + radius * sinf(theta2), 
            z, c.r, c.g, c.b, c.a,
        });

        batch->vertex_count += 3;
    }
}

void cog_draw_circle_lines(cog_window* window, float x, float y, float radius, float thickness, int segments, cog_color color) {
    segments = segments ? segments : 36; 
    float angle_step = (2.0f * M_PI) / segments;
    float r_out = radius;
    float r_in = radius - thickness;
    float z = 0.0f;
    cog_colorf c = cog_color_to_colorf(color);
    
    cog_renderer* r = window->renderer;
    r->auto_origin = (cog_vec2){ x, y };

    cog_batch* batch = _cog_get_batch(r, 0);

    for (int i = 0; i < segments; i++) {
        float theta1 = i * angle_step;
        float theta2 = (i + 1) * angle_step;
    
        float cos1 = cosf(theta1), sin1 = sinf(theta1);
        float cos2 = cosf(theta2), sin2 = sinf(theta2);

        float p1x = x + r_out * cos1, p1y = y + r_out * sin1;
        float p2x = x + r_out * cos2, p2y = y + r_out * sin2;

        float p3x = x + r_in * cos1, p3y = y + r_in * sin1;
        float p4x = x + r_in * cos2, p4y = y + r_in * sin2;

        _cog_push_vertex(r, (cog_vertex){ p1x, p1y, z, c.r, c.g, c.b, c.a, 0.0f, 0.0f });
        _cog_push_vertex(r, (cog_vertex){ p2x, p2y, z, c.r, c.g, c.b, c.a, 0.0f, 0.0f });
        _cog_push_vertex(r, (cog_vertex){ p3x, p3y, z, c.r, c.g, c.b, c.a, 0.0f, 0.0f });

        _cog_push_vertex(r, (cog_vertex){ p2x, p2y, z, c.r, c.g, c.b, c.a, 0.0f, 0.0f });
        _cog_push_vertex(r, (cog_vertex){ p3x, p3y, z, c.r, c.g, c.b, c.a, 0.0f, 0.0f });
        _cog_push_vertex(r, (cog_vertex){ p4x, p4y, z, c.r, c.g, c.b, c.a, 0.0f, 0.0f });

        batch->vertex_count += 6;
    }
}

void cog_draw_texture(cog_window* window, cog_texture* texture, float x, float y, float width, float height, cog_color color) {
    float x1 = x;
    float y1 = y;
    float x2 = x + width;
    float y2 = y + height;
    float z = 0.0f;
    cog_colorf c = cog_color_to_colorf(color);
    
    cog_renderer* r = window->renderer;
    r->auto_origin = (cog_vec2){ x + width * 0.5f, y + height * 0.5f };

    cog_batch* batch = _cog_get_batch(r, texture->id);

    _cog_push_vertex(r, (cog_vertex){ x1, y1, z, c.r, c.g, c.b, c.a, 0.0f, 0.0f });
    _cog_push_vertex(r, (cog_vertex){ x2, y1, z, c.r, c.g, c.b, c.a, 1.0f, 0.0f });
    _cog_push_vertex(r, (cog_vertex){ x1, y2, z, c.r, c.g, c.b, c.a, 0.0f, 1.0f });

    _cog_push_vertex(r, (cog_vertex){ x1, y2, z, c.r, c.g, c.b, c.a, 0.0f, 1.0f });
    _cog_push_vertex(r, (cog_vertex){ x2, y1, z, c.r, c.g, c.b, c.a, 1.0f, 0.0f });
    _cog_push_vertex(r, (cog_vertex){ x2, y2, z, c.r, c.g, c.b, c.a, 1.0f, 1.0f });

    batch->vertex_count += 6;
}

void cog_draw_text(cog_window* window, cog_font* font, const char* text, float x, float y, float fontsize, cog_color color) {
    float scale = fontsize / font->size;

    int ascent, descent, line_gap;
    stbtt_GetFontVMetrics(&font->info, &ascent, &descent, &line_gap);
    
    float ascent_px = (float)ascent * font->scale * scale;
    float line_height = (float)(ascent - descent + line_gap) * font->scale * scale;

    float cursor_x = x;
    float cursor_y = y + ascent_px;

    cog_colorf c = cog_color_to_colorf(color);

    cog_renderer* r = window->renderer;
    if (r->rotation != 0.0f && r->rotation_origin.x == -1.0f && r->rotation_origin.y == -1.0f) {
        cog_vec2 size = cog_measure_text(font, text, fontsize);
        r->auto_origin = (cog_vec2){ x + size.x * 0.5f, y + size.y * 0.5f };
    }

    cog_batch* batch = _cog_get_batch(r, font->texture->id);

    const char* ptr = text;
    while (*ptr) {
        uint32_t codepoint = _cog_utf8_decode(&ptr);

        if (codepoint == '\n') {
            cursor_x = x;
            cursor_y += line_height;
            continue;
        }

        cog_glyph* g = _cog_get_or_load_glyph(font, codepoint);
        if (!g) continue;

        float x1 = cursor_x + g->x0 * scale;
        float y1 = cursor_y + g->y0 * scale;
        float x2 = cursor_x + g->x1 * scale;
        float y2 = cursor_y + g->y1 * scale;
        float z  = 0.0f;

        if (x2 > x1 && y2 > y1) {
            _cog_push_vertex(r, (cog_vertex){ x1, y1, z, c.r, c.g, c.b, c.a, g->u0, g->v0 });
            _cog_push_vertex(r, (cog_vertex){ x2, y1, z, c.r, c.g, c.b, c.a, g->u1, g->v0 });
            _cog_push_vertex(r, (cog_vertex){ x1, y2, z, c.r, c.g, c.b, c.a, g->u0, g->v1 });

            _cog_push_vertex(r, (cog_vertex){ x1, y2, z, c.r, c.g, c.b, c.a, g->u0, g->v1 });
            _cog_push_vertex(r, (cog_vertex){ x2, y1, z, c.r, c.g, c.b, c.a, g->u1, g->v0 });
            _cog_push_vertex(r, (cog_vertex){ x2, y2, z, c.r, c.g, c.b, c.a, g->u1, g->v1 });

            batch->vertex_count += 6;
        }

        cursor_x += g->x_offset * scale;
    }
}

void cog_render(cog_window *window) {
    if (!window) return;
    
    cog_renderer* r = window->renderer;
    if (r->vertex_count > 0) {
        glUseProgram(r->program);
        glBindVertexArray(r->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, r->VBO);
        
        glUniform2f(r->loc_resolution, (float)window->width, (float)window->height);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glBufferData(GL_ARRAY_BUFFER, r->vertex_count * sizeof(cog_vertex), r->vertices, GL_DYNAMIC_DRAW);
        
        for (size_t i = 0; i < r->batch_count; i++) {
            cog_batch* batch = &r->batches[i];
            if (batch->vertex_count == 0) continue;
            
            glUniform1i(r->loc_use_texture, batch->texture_id > 0);
            glBindTexture(GL_TEXTURE_2D, batch->texture_id);
            
            glDrawArrays(GL_TRIANGLES, batch->vertex_start, batch->vertex_count);
        }
        
        glUniform1i(r->loc_use_texture, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    if (window->device_context) {
        SwapBuffers(window->device_context);
    }
    
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);

    if (window->target_fps > 0) {
        double target_sec = 1.0 / (double)window->target_fps;
        double elapsed = (double)(current_time.QuadPart - window->last_frame_time.QuadPart) / (double)window->timer_frequency.QuadPart;

        while (elapsed < target_sec) {
            double remaining = target_sec - elapsed;
            if (remaining > 0.002) {
                Sleep((DWORD)((remaining - 0.001) * 1000.0));
            }
            QueryPerformanceCounter(&current_time);
            elapsed = (double)(current_time.QuadPart - window->last_frame_time.QuadPart) / (double)window->timer_frequency.QuadPart;
        }
    }

    window->delta_time = (float)((double)(current_time.QuadPart - window->last_frame_time.QuadPart) / (double)window->timer_frequency.QuadPart);
    window->last_frame_time = current_time;

    r->vertex_count = 0;
    r->batch_count = 0;

    _cog_reset_window(window);
}

cog_color cog_rgba_to_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (cog_color) { r, g, b, a };
}

cog_color cog_rgbaf_to_color(float r, float g, float b, float a) {
    return (cog_color) {
        (unsigned char)(r * 255.0f),
        (unsigned char)(g * 255.0f),
        (unsigned char)(b * 255.0f),
        (unsigned char)(a * 255.0f)
    };
}

cog_color cog_colorf_to_color(cog_colorf colorf) {
    return (cog_color) {
        (unsigned char)(colorf.r * 255.0f),
        (unsigned char)(colorf.g * 255.0f),
        (unsigned char)(colorf.b * 255.0f),
        (unsigned char)(colorf.a * 255.0f)
    };
}

cog_color cog_hex_to_color(uint32_t hex_color) {
    return (cog_color) {
        (unsigned char)((hex_color >> 24) & 0xff),
        (unsigned char)((hex_color >> 16) & 0xff),
        (unsigned char)((hex_color >> 8)  & 0xff),
        (unsigned char)((hex_color >> 0)  & 0xff)
    };
}

cog_colorf cog_rgba_to_colorf(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (cog_colorf) {
        (float)r / 255.0f,
        (float)g / 255.0f,
        (float)b / 255.0f,
        (float)a / 255.0f
    };
}

cog_colorf cog_rgbaf_to_colorf(float r, float g, float b, float a) {
    return (cog_colorf) { r, g, b, a };
}

cog_colorf cog_color_to_colorf(cog_color color) {
    return (cog_colorf) {
        (float)color.r / 255.0f,
        (float)color.g / 255.0f,
        (float)color.b / 255.0f,
        (float)color.a / 255.0f
    };
}

cog_colorf cog_hex_to_colorf(uint32_t hex_color) {
    return (cog_colorf) {
        (float)((hex_color >> 24) & 0xff) / 255.0f,
        (float)((hex_color >> 16) & 0xff) / 255.0f,
        (float)((hex_color >> 8)  & 0xff) / 255.0f,
        (float)((hex_color >> 0)  & 0xff) / 255.0f
    };
}

uint32_t cog_rgba_to_hex(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8)  | (uint32_t)a);
}

uint32_t cog_rgbaf_to_hex(float r, float g, float b, float a) {
    return (
        ((uint32_t)(r * 255.0f) << 24) |
        ((uint32_t)(g * 255.0f) << 16) |
        ((uint32_t)(b * 255.0f) << 8)  |
        ((uint32_t)(a * 255.0f) << 0)
    );
}

uint32_t cog_color_to_hex(cog_color color) {
    return (((uint32_t)color.r << 24) | ((uint32_t)color.g << 16) | ((uint32_t)color.b << 8)  | (uint32_t)color.a);
}

uint32_t cog_colorf_to_hex(cog_colorf colorf) {
    return (
        ((uint32_t)(colorf.r * 255.0f) << 24) |
        ((uint32_t)(colorf.g * 255.0f) << 16) |
        ((uint32_t)(colorf.b * 255.0f) << 8)  |
        ((uint32_t)(colorf.a * 255.0f) << 0)
    );
}

bool cog_is_point_in_rect(cog_vec2 point, cog_rect rect) {
    return (rect.x <= point.x && point.x <= rect.x + rect.width) && (rect.y <= point.y && point.y <= rect.y + rect.height);
}

cog_vec2 cog_measure_text(cog_font* font, const char* text, float fontsize) {
    float scale = fontsize / font->size;

    int ascent, descent, line_gap;
    stbtt_GetFontVMetrics(&font->info, &ascent, &descent, &line_gap);
    float line_height = (float)(ascent - descent + line_gap) * font->scale * scale;

    float max_width = 0.0f;
    float current_width = 0.0f;
    int line_count = 1;

    const char* ptr = text;
    while (*ptr) {
        uint32_t codepoint = _cog_utf8_decode(&ptr);

        if (codepoint == '\n') {
            if (current_width > max_width) {
                max_width = current_width;
            }
            current_width = 0.0f;
            line_count++;
            continue;
        }

        cog_glyph* g = _cog_get_or_load_glyph(font, codepoint);
        if (g) {
            current_width += g->x_offset * scale;
        }
    }

    if (current_width > max_width) {
        max_width = current_width;
    }

    float total_height = (float)line_count * line_height;

    return (cog_vec2){ max_width, total_height };
}

#endif // COG_IMPLEMENTATION