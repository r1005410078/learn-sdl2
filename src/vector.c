#include "vector.h"
#include <math.h>

vec3_t vec3_t_rotate_x(vec3_t v, float angle) {
  vec3_t rotate_vector = {
    .x = v.x,
    .y = v.y * cos(angle) - v.z * sin(angle),
    .z = v.y * sin(angle) + v.z * cos(angle), 
  };
  
  return rotate_vector;
}

vec3_t vec3_t_rotate_y(vec3_t v, float angle) {
  vec3_t rotate_vector = {
    .x = v.x * cos(angle) - v.z * sin(angle),
    .y = v.y, 
    .z = v.x * sin(angle) + v.z * cos(angle)
  };

  return rotate_vector;
}

vec3_t vec3_t_rotate_z(vec3_t vec, float angle) {
  vec3_t rotate_vector = {
    .x = vec.x * cos(angle) - vec.y * sin(angle),
    .y = vec.x * sin(angle) + vec.y * cos(angle),
    .z = vec.z
  };
  return rotate_vector;
}