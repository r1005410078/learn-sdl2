#ifndef VECTOR_H
#define VECTOR_H

typedef struct 
{
  float x, y;
} vec2_t;

typedef struct 
{
  float x, y, z;
} vec3_t;

vec3_t vec3_t_rotate_x(vec3_t vec, float angle);

vec3_t vec3_t_rotate_y(vec3_t vec, float angle);

vec3_t vec3_t_rotate_z(vec3_t vec, float angle);

#endif
