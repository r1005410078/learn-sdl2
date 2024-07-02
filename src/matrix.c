#include "matrix.h"
#include <math.h>

mat4_t mat4_identity(void)
{
  // [1 0 0 0]
  // [0 1 0 0]
  // [0 0 1 0]
  // [0 0 0 1]

  mat4_t mat = {
      .m = {
          {1, 0, 0, 0},
          {0, 1, 0, 0},
          {0, 0, 1, 0},
          {0, 0, 0, 1},
      }};

  return mat;
}

mat4_t mat4_make_scale(float x, float y, float z)
{
  // [sx 0 0 0]
  // [0 sy 0 0]
  // [0 0 sz 0]
  // [0 0 0 1]
  mat4_t mat = mat4_identity();

  mat.m[0][0] = x;
  mat.m[1][1] = y;
  mat.m[2][2] = z;

  return mat;
}

mat4_t mat4_make_translate(float tx, float ty, float tz)
{
  // [1 0 0 tx]
  // [0 1 0 ty]
  // [0 0 1 tz]
  // [0 0 0 1]

  mat4_t mat = mat4_identity();
  mat.m[0][3] = tx;
  mat.m[1][3] = ty;
  mat.m[2][3] = tz;

  return mat;
}

mat4_t mat4_make_rotate_x(float angle)
{
  mat4_t mat = mat4_identity();
  mat.m[1][1] = cos(angle);
  mat.m[1][2] = -sin(angle);
  mat.m[2][1] = sin(angle);
  mat.m[2][2] = cos(angle);
  return mat;
}

mat4_t mat4_make_rotate_y(float angle)
{
  mat4_t mat = mat4_identity();
  mat.m[0][0] = cos(angle);
  mat.m[0][2] = sin(angle);
  mat.m[2][0] = -sin(angle);
  mat.m[2][2] = cos(angle);
  return mat;
}

mat4_t mat4_make_rotate_z(float angle)
{
  mat4_t mat = mat4_identity();
  mat.m[0][0] = cos(angle);
  mat.m[0][1] = -sin(angle);
  mat.m[1][0] = sin(angle);
  mat.m[1][1] = cos(angle);
  return mat;
}

mat4_t mat4_mul_mat4(mat4_t m1, mat4_t m2)
{
  mat4_t m;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      m.m[i][j] = m1.m[i][0] * m2.m[0][j] + m1.m[i][1] * m2.m[1][j] + m1.m[i][2] * m2.m[2][j] + m1.m[i][3] * m2.m[3][j];
    }
  }

  return m;
}

vec4_t mat4_mul_vec4(mat4_t m1, vec4_t m2)
{
  vec4_t m;

  m.x = m1.m[0][0] * m2.x + m1.m[0][1] * m2.y + m1.m[0][2] * m2.z + m1.m[0][3] * m2.w;
  m.y = m1.m[1][0] * m2.x + m1.m[1][1] * m2.y + m1.m[1][2] * m2.z + m1.m[1][3] * m2.w;
  m.z = m1.m[2][0] * m2.x + m1.m[2][1] * m2.y + m1.m[2][2] * m2.z + m1.m[2][3] * m2.w;
  m.w = m1.m[3][0] * m2.x + m1.m[3][1] * m2.y + m1.m[3][2] * m2.z + m1.m[3][3] * m2.w;

  return m;
}

mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar)
{

  mat4_t mat = {{{0}}};

  mat.m[0][0] = aspect * (1 / tan(fov / 2));
  mat.m[1][1] = 1 / tan(fov / 2);
  mat.m[2][2] = zfar / (zfar - znear);
  mat.m[2][3] = (-zfar * znear) / (zfar - znear);
  mat.m[3][2] = 1.0;

  return mat;
}

vec4_t mat4_mul_vec4_project(mat4_t mat_proj, vec4_t v)
{
  vec4_t result = mat4_mul_vec4(mat_proj, v);

  if (result.w != 0.0)
  {
    result.x /= result.w;
    result.y /= result.w;
    result.z /= result.w;
  }

  return result;
}
