#ifndef MODEL_H
#define MODEL_H

#include "geometry.h"


typedef struct {
    int vertices[3];
    int textures[3];
    int normals[3];
} face;


typedef struct {
    int n_vertices;
    int n_faces;
    vec3f *vertices;
    face *faces;
} model;


int count_char(FILE *file_ptr, const char a);
void read_face(FILE *file_ptr, face *const f);
void read_model(model *const m, const char *file_name);
void free_model(model *const m);


#endif // MODEL_H
