#include "display.h"
#include "vector.h"
#include "array.h"
#include "mesh.h"

triangle_t *triangle_to_render;

// 摄像机的位置
vec3_t camera_position = {.x = 0, .y = 0, .z = -5};

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

void process_input(void)
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
      is_running = false;
    }
    break;
  default:
    break;
  }
}

vec2_t project(vec3_t point)
{
  vec2_t project_point = {
      .x = (fov_factor * point.x) / point.z,
      .y = (fov_factor * point.y) / point.z};

  return project_point;
}

void update(void)
{

  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time);
  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
  {
    SDL_Delay(time_to_wait);
  }

  triangle_to_render = NULL;
  previous_frame_time = SDL_GetTicks();

  mesh.rotation.x += 0.01;
  mesh.rotation.y += 0.01;
  mesh.rotation.z += 0.01;

  int num_faces = array_length(mesh.faces);

  for (int i = 0; i < num_faces; i++)
  {
    face_t mesh_face = mesh.faces[i];

    vec3_t face_vertices[3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    triangle_t project_triangle;

    for (int j = 0; j < 3; j++)
    {
      vec3_t transformed_vertex = face_vertices[j];

      // transformed_vertex = vec3_t_rotate_x(transformed_vertex, mesh.rotation.x);
      transformed_vertex = vec3_t_rotate_y(transformed_vertex, mesh.rotation.y);
      // transformed_vertex = vec3_t_rotate_z(transformed_vertex, mesh.rotation.z);

      transformed_vertex.z -= camera_position.z;

      vec2_t project_point = project(transformed_vertex);

      project_point.x += window_width / 2;
      project_point.y += window_height / 2;

      project_triangle.points[j] = project_point;
    }

    array_push(triangle_to_render, project_triangle);
  }
}

void render(void)
{
  draw_grid();

  size_t triangle_count = array_length(triangle_to_render);
  for (size_t i = 0; i < triangle_count; i++)
  {
    triangle_t triangle = triangle_to_render[i];

    draw_triangle(
        triangle.points[0].x,
        triangle.points[0].y,
        triangle.points[1].x,
        triangle.points[1].y,
        triangle.points[2].x,
        triangle.points[2].y,
        0xFF00FF00);

    draw_rect(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFF00FF00);
    draw_rect(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFF00FF00);
    draw_rect(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFF00FF00);
  }

  array_free(triangle_to_render);

  render_color_buffer();
  clear_color_buffer(0xFF000000);
  SDL_RenderPresent(renderer);
}

void setup(void)
{
  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
  color_buffer_texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STATIC,
      window_width,
      window_height);

  load_obj_file_data("./src/assets/monkey.obj");
}

int main(void)
{
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