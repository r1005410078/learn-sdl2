#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "triangle.h"

#define N_NESH_VERTICES 8
extern vec3_t cube_vertices[N_NESH_VERTICES];

#define N_MESH_FACES (6 * 2) // 6 faces, 2 triangles per face
extern face_t cube__faces[N_MESH_FACES];

void load_obj_file_data(char *filename);

void load_cube_mesh_data(void);

typedef struct
{
  vec3_t *vertices;
  face_t *faces;
  vec3_t rotation;
} mesh_t;

extern mesh_t mesh;

#endif