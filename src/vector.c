#include "vector.h"
#include <math.h>

vec2_t vec2_add(vec2_t v1, vec2_t v2)
{
  vec2_t result = {
      .x = v1.x + v2.x,
      .y = v1.y + v2.y};
  return result;
}

vec2_t vec2_sub(vec2_t v1, vec2_t v2)
{
  vec2_t result = {
      .x = v1.x - v2.x,
      .y = v1.y - v2.y};
  return result;
}

vec2_t vec2_mul(vec2_t v1, float factor)
{
  vec2_t result = {
      .x = v1.x * factor,
      .y = v1.y * factor};
  return result;
}

vec2_t vec2_div(vec2_t v1, float factor)
{
  vec2_t result = {
      .x = v1.x / factor,
      .y = v1.y / factor};
  return result;
}

void normalize_vec2(vec2_t *v)
{
  float length = sqrt(v->x * v->x + v->y * v->y);

  v->x = v->x / length;
  v->y = v->y / length;
}

float vec3_length(vec3_t v)
{
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3_t vec3_add(vec3_t v1, vec3_t v2)
{
  vec3_t result = {
      .x = v1.x + v2.x,
      .y = v1.y + v2.y,
      .z = v1.z + v2.z};
  return result;
}

vec3_t vec3_sub(vec3_t v1, vec3_t v2)
{
  vec3_t result = {
      .x = v1.x - v2.x,
      .y = v1.y - v2.y,
      .z = v1.z - v2.z};
  return result;
}

vec3_t vec3_mul(vec3_t v1, float factor)
{
  vec3_t result = {
      .x = v1.x * factor,
      .y = v1.y * factor,
      .z = v1.z * factor};
  return result;
}

vec3_t vec3_div(vec3_t v1, float factor)
{
  vec3_t result = {
      .x = v1.x / factor,
      .y = v1.y / factor,
      .z = v1.z / factor};
  return result;
}

vec3_t vec3_cross(vec3_t v1, vec3_t v2)
{
  vec3_t result = {
      .x = v1.y * v2.z - v1.z * v2.y,
      .y = v1.z * v2.x - v1.x * v2.z,
      .z = v1.x * v2.y - v1.y * v2.x};

  return result;
}

float vec3_dot(vec3_t v1, vec3_t v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void normalize_vec3(vec3_t *v)
{
  float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);

  v->x = v->x / length;
  v->y = v->y / length;
  v->z = v->z / length;
}

vec3_t vec3_t_rotate_x(vec3_t v, float angle)
{
  vec3_t rotate_vector = {
      .x = v.x,
      .y = v.y * cos(angle) - v.z * sin(angle),
      .z = v.y * sin(angle) + v.z * cos(angle),
  };

  return rotate_vector;
}

vec3_t vec3_t_rotate_y(vec3_t v, float angle)
{
  vec3_t rotate_vector = {
      .x = v.x * cos(angle) - v.z * sin(angle),
      .y = v.y,
      .z = v.x * sin(angle) + v.z * cos(angle)};

  return rotate_vector;
}

vec3_t vec3_t_rotate_z(vec3_t vec, float angle)
{
  vec3_t rotate_vector = {
      .x = vec.x * cos(angle) - vec.y * sin(angle),
      .y = vec.x * sin(angle) + vec.y * cos(angle),
      .z = vec.z};
  return rotate_vector;
}

float vec2_length(vec2_t v)
{
  return sqrt(v.x * v.x + v.y * v.y);
}
