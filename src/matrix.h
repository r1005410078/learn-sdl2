#ifndef MATRIX_H
#define MATRIX_H
#include "vector.h"

typedef struct
{
  float m[4][4];
} mat4_t;

mat4_t mat4_identity(void);
mat4_t mat4_make_scale(float x, float y, float z);
mat4_t mat4_make_translate(float x, float y, float z);
mat4_t mat4_make_rotate_x(float angle);
mat4_t mat4_make_rotate_y(float angle);
mat4_t mat4_make_rotate_z(float angle);
mat4_t mat4_mul_mat4(mat4_t m1, mat4_t m2);
vec4_t mat4_mul_vec4(mat4_t m1, vec4_t m2);
mat4_t mat4_make_perspective(float fov, float aspect, float znear, float zfar);
vec4_t mat4_mul_vec4_project(mat4_t mat_proj, vec4_t v);
#endif