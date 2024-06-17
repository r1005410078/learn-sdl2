#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *color_buffer_texture;

extern uint32_t *color_buffer;
extern int window_width;
extern int window_height;

bool initialize_window(void);
void render_color_buffer(void);
void draw_grid(void);
void draw_pixel(u_int32_t x, u_int32_t y, u_int32_t color);
void clear_color_buffer(u_int32_t color);
void draw_rect(u_int32_t x, u_int32_t y, u_int32_t w, u_int32_t h, u_int32_t color);
void destroy_window(void);

#endif