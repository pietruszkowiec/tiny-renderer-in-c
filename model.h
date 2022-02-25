#ifndef MODEL_H
#define MODEL_H

#include "geometry.h"


typedef struct {
    int n_vertices;
    int *vertices;
    int *textures;
    int *normals;
} face;


typedef struct {
    int n_vertices;
    int n_faces;
    vec3f *vertices;
    face *faces;
} model;


void free_face(face *const f);
int count_char(FILE *file_ptr, const char a);
void read_face(FILE *file_ptr, face *const f);
void read_model(model *const m, const char *file_name);
void free_model(model *const m);


#endif // MODEL_H
