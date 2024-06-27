#include "display.h"
#include "vector.h"
#include "array.h"
#include "mesh.h"

triangle_t *triangle_to_render;

// 摄像机的位置
vec3_t camera_position = {.x = 0, .y = 0, .z = 0};

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

    if (event.key.keysym.sym == SDLK_1)
    {
      render_method = RENDER_WIRE_VERTEX;
    }

    if (event.key.keysym.sym == SDLK_2)
    {
      render_method = RENDER_WIRE;
    }

    if (event.key.keysym.sym == SDLK_3)
    {
      render_method = RENDER_FILL_TRIANGLE;
    }

    if (event.key.keysym.sym == SDLK_4)
    {
      render_method = RENDER_FILL_TRIANGLE_WIRE;
    }

    if (event.key.keysym.sym == SDLK_c)
    {
      cull_method = CULL_BACKFACE;
    }

    if (event.key.keysym.sym == SDLK_d)
    {
      cull_method = CULL_NONE;
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

    vec3_t transformed_vertexes[3];

    for (int j = 0; j < 3; j++)
    {
      vec3_t transformed_vertex = face_vertices[j];

      transformed_vertex = vec3_t_rotate_x(transformed_vertex, mesh.rotation.x);
      transformed_vertex = vec3_t_rotate_y(transformed_vertex, mesh.rotation.y);
      transformed_vertex = vec3_t_rotate_z(transformed_vertex, mesh.rotation.z);

      transformed_vertex.z += 5;

      transformed_vertexes[j] = transformed_vertex;
    }

    if (cull_method == CULL_BACKFACE)
    {
      ///    A
      ///  /   \
      /// B     C
      vec3_t vector_a = transformed_vertexes[0];
      vec3_t vector_b = transformed_vertexes[1];
      vec3_t vector_c = transformed_vertexes[2];

      vec3_t vector_ab = vec3_sub(vector_b, vector_a);
      vec3_t vector_ac = vec3_sub(vector_c, vector_a);

      normalize_vec3(&vector_ab);
      normalize_vec3(&vector_ac);

      vec3_t normal = vec3_cross(vector_ab, vector_ac);

      normalize_vec3(&normal);

      vec3_t dot_normal_camera = vec3_sub(camera_position, vector_a);

      if (vec3_dot(normal, dot_normal_camera) < 0)
      {
        continue;
      }
    }

    vec2_t project_points[3];

    for (int i = 0; i < 3; i++)
    {
      vec3_t transformed_vertex = transformed_vertexes[i];
      project_points[i] = project(transformed_vertex);
      project_points[i].x += window_width / 2;
      project_points[i].y += window_height / 2;
    }

    float avg_depth = (project_points[0].y + project_points[1].y + project_points[2].y) / 3.0;

    triangle_t project_triangle = {
        .points = {
            {project_points[0].x, project_points[0].y},
            {project_points[1].x, project_points[1].y},
            {project_points[2].x, project_points[2].y}},
        .color = mesh_face.color,
        .avg_depth = avg_depth};

    array_push(triangle_to_render, project_triangle);
  }

  int num_triangles = array_length(triangle_to_render);
  for (int i = 0; i < num_triangles; i++)
  {
    for (int j = i; j < num_triangles; j++)
    {
      if (triangle_to_render[i].avg_depth < triangle_to_render[j].avg_depth)
      {
        triangle_t tmp = triangle_to_render[i];
        triangle_to_render[i] = triangle_to_render[j];
        triangle_to_render[j] = tmp;
      }
    }
  }
}

void render(void)
{
  draw_grid();

  int triangle_count = array_length(triangle_to_render);
  for (int i = 0; i < triangle_count; i++)
  {
    triangle_t triangle = triangle_to_render[i];

    if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE)
    {
      draw_filled_triangle(
          triangle.points[0].x,
          triangle.points[0].y,
          triangle.points[1].x,
          triangle.points[1].y,
          triangle.points[2].x,
          triangle.points[2].y,
          triangle.color);
    }

    if (render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX || render_method == RENDER_FILL_TRIANGLE_WIRE)
    {
      draw_triangle(
          triangle.points[0].x,
          triangle.points[0].y,
          triangle.points[1].x,
          triangle.points[1].y,
          triangle.points[2].x,
          triangle.points[2].y,
          0xFFFFFFFF);
    }

    if (render_method == RENDER_WIRE_VERTEX)
    {
      draw_rect(triangle.points[0].x - 3, triangle.points[0].y - 3, 6, 6, 0xFF00FF00);
      draw_rect(triangle.points[1].x - 3, triangle.points[1].y - 3, 6, 6, 0xFF00FF00);
      draw_rect(triangle.points[2].x - 3, triangle.points[2].y - 3, 6, 6, 0xFF00FF00);
    }
  }

  // draw_filled_triangle(300, 100, 50, 400, 500, 700, 0xFF00FF00);

  array_free(triangle_to_render);

  render_color_buffer();
  clear_color_buffer(0xFF000000);
  SDL_RenderPresent(renderer);
}

void setup(void)
{
  render_method = RENDER_WIRE;
  cull_method = CULL_BACKFACE;

  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * window_width * window_height);
  color_buffer_texture = SDL_CreateTexture(
      renderer,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STATIC,
      window_width,
      window_height);

  // load_obj_file_data("./src/assets/cube.obj");
  load_cube_mesh_data();
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