#include "display.h"
#include "vector.h"

bool is_running = true;

const int N_POINTS = 9 * 9 * 9;
const float fov_factor = 128;
vec3_t cube_points[N_POINTS];
vec2_t project_points[N_POINTS];


void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
    case SDL_QUIT:
      is_running = false;
      break;
    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        is_running = false;
      }
      break;
    default:
      break;
  }
}

vec2_t project (vec3_t point) {
  vec2_t project_point = {
    .x = fov_factor * point.x,
    .y = fov_factor * point.y
  };

  return project_point;
}

void update(void) {
  // TODO
  for (int i = 0; i < N_POINTS; i++) {
    vec3_t point = cube_points[i];
    vec2_t project_point = project(point);
    project_points[i] = project_point;
  }
}

void render(void) {
  // TODO
  // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  // SDL_RenderClear(renderer);

  draw_grid();
  // draw_rect(300, 200, 300, 150, 0xFF00FF00);

  for (size_t i = 0; i < N_POINTS; i++)
  {
    vec2_t point = project_points[i];
    draw_rect(
      point.x + window_width / 2, 
      point.y + window_height / 2, 
      4, 
      4, 
      0xFF00FF00
    );
  }
  

  render_color_buffer();
  clear_color_buffer(0xFF000000);
  SDL_RenderPresent(renderer);
}

void setup(void) {
  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
  color_buffer_texture = SDL_CreateTexture(
    renderer, 
    SDL_PIXELFORMAT_ARGB8888, 
    SDL_TEXTUREACCESS_STATIC, 
    window_width, 
    window_height
  );

  int point_count = 0;
  for (float x = -1; x <= 1; x+=0.25) {
    for (float y = -1; y <= 1; y+=0.25) {
      for (float z = -1; z <= 1; z+=0.25) {
        vec3_t new_point = (vec3_t) {x, y, z};
        cube_points[point_count++] = new_point;
      }
    }
  }
}

int main(void) {
  is_running = initialize_window();

  setup();

  while (is_running)
  {
    // 处理事件
    process_input();
    // 更新
    update();
    // 渲染
    render();
  }

  destroy_window();
  
  return 0;
}