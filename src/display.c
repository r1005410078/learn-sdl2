#include "display.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;

uint32_t *color_buffer = NULL;
int window_width = 800;
int window_height = 600;

bool initialize_window(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  SDL_DisplayMode display;
  SDL_GetCurrentDisplayMode(0, &display);
  window_width = display.w;
  window_height = display.h;

  window = SDL_CreateWindow(
      "Hello, World!",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      window_width,
      window_height,
      SDL_WINDOW_SHOWN);

  if (window == NULL)
  {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == NULL)
  {
    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void render_color_buffer(void)
{
  // TODO
  SDL_UpdateTexture(
      color_buffer_texture,
      NULL,
      color_buffer,
      window_width * sizeof(uint32_t));
  SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid(void)
{
  for (u_int32_t y = 0; y < window_height; y++)
  {
    for (u_int32_t x = 0; x < window_width; x++)
    {
      if (x % 20 == 0 || y % 20 == 0)
      {
        draw_pixel(x, y, 0xFF333333);
      }
    }
  }
}

void clear_color_buffer(u_int32_t color)
{
  for (u_int32_t y = 0; y < window_height; y++)
  {
    for (uint32_t x = 0; x < window_width; x++)
    {
      color_buffer[y * window_width + x] = color;
    }
  }
  // TODO
}

void draw_rect(u_int32_t x, u_int32_t y, u_int32_t w, u_int32_t h, u_int32_t color)
{
  // TODO
  for (uint32_t i = 0; i < h; i++)
  {
    for (size_t j = 0; j < w; j++)
    {
      draw_pixel(x + j, y + i, color);
    }
  }
}

void draw_line(u_int32_t x0, u_int32_t y0, u_int32_t x1, u_int32_t y1, u_int32_t color)
{
  // DDA 算法
  int delta_x = x1 - x0;
  int delta_y = y1 - y0;

  int longest_side_length = abs(delta_x) > abs(delta_y) ? abs(delta_x) : abs(delta_y);

  float increment_x = delta_x / (float)longest_side_length;
  float increment_y = delta_y / (float)longest_side_length;

  float current_x = x0;
  float current_y = y0;

  for (u_int32_t i = 0; i < longest_side_length; i++)
  {
    draw_pixel(round(current_x), round(current_y), color);
    current_x += increment_x;
    current_y += increment_y;
  }
}

void draw_triangle(u_int32_t x0, u_int32_t y0, u_int32_t x1, u_int32_t y1, u_int32_t x2, u_int32_t y2, u_int32_t color)
{
  draw_line(x0, y0, x1, y1, color);
  draw_line(x1, y1, x2, y2, color);
  draw_line(x2, y2, x0, y0, color);
}

void draw_pixel(u_int32_t x, u_int32_t y, u_int32_t color)
{
  // TODO
  color_buffer[y * window_width + x] = color;
}

void destroy_window(void)
{
  free(color_buffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
