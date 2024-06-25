#ifndef VECTOR_H
#define VECTOR_H

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 2D Vector
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
  float x, y;
} vec2_t;

float vec2_length(vec2_t v);
vec2_t vec2_add(vec2_t v1, vec2_t v2);
vec2_t vec2_sub(vec2_t v1, vec2_t v2);
vec2_t vec2_mul(vec2_t v1, float factor);
vec2_t vec2_div(vec2_t v1, float factor);
void normalize_vec2(vec2_t *v);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 3D Vector
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
  float x, y, z;
} vec3_t;

float vec3_length(vec3_t v);
vec3_t vec3_add(vec3_t v1, vec3_t v2);
vec3_t vec3_sub(vec3_t v1, vec3_t v2);
vec3_t vec3_mul(vec3_t v1, float factor);
vec3_t vec3_div(vec3_t v1, float factor);
vec3_t vec3_cross(vec3_t v1, vec3_t v2);
float vec3_dot(vec3_t v1, vec3_t v2);
void normalize_vec3(vec3_t *v);

vec3_t vec3_t_rotate_x(vec3_t vec, float angle);
vec3_t vec3_t_rotate_y(vec3_t vec, float angle);
vec3_t vec3_t_rotate_z(vec3_t vec, float angle);

#endif
