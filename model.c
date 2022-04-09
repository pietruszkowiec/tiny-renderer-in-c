#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "geometry.h"


void free_face(face *const f) {
    free(f->vertices);
    free(f->textures);
    free(f->normals);
}


int count_char(FILE *file_ptr, const char a) {
    int n = 0;
    char c = '\0';
    
    rewind(file_ptr);

    while ((c = getc(file_ptr)) != EOF) {
        if (c == a) {
            c = getc(file_ptr);
            
            if (c == EOF)
                break;
            if (c == ' ')
                n++;
        }
    }

    rewind(file_ptr);

    return n;
}


int count_vertices_in_face(FILE *file_ptr) {
    int i = 1;
    int n = 1;
    char c;

    while ((c = getc(file_ptr)) != '\n' && c != EOF) {
        i++;
        if (c == ' ')
            n++;
    }

    fseek(file_ptr, -i, SEEK_CUR);

    return n;
}


void read_face(FILE *file_ptr, face *const f) {
    f->n_vertices = count_vertices_in_face(file_ptr);

    f->vertices = calloc(f->n_vertices, sizeof *(f->vertices));
    f->textures = calloc(f->n_vertices, sizeof *(f->textures));
    f->normals = calloc(f->n_vertices, sizeof *(f->normals));

    if (!(f->vertices) || !(f->textures) || !(f->normals)){
        fprintf(stderr, "can't allocate memory\n");
        exit(1);
    }

    char c;

    for (int i = 0; i < f->n_vertices; i++) {
        f->vertices[i] = -1;
        f->textures[i] = -1;
        f->normals[i] = -1;

        fscanf(file_ptr, "%i", &(f->vertices[i]));
        f->vertices[i]--;

        if ((c = getc(file_ptr)) == ' ' || c == '\n')
            continue;
        
        if ((c = getc(file_ptr)) != '/') {
            fseek(file_ptr, -1, SEEK_CUR);
            fscanf(file_ptr, "%i", &(f->textures[i]));
            f->textures[i]--;
        } else {
            fseek(file_ptr, -1, SEEK_CUR);
        }

        if ((c = getc(file_ptr)) == ' ' || c == '\n')
            continue;
        
        if ((c = getc(file_ptr)) == ' ' || c == '\n')
            continue;

        fseek(file_ptr, -1, SEEK_CUR);
        fscanf(file_ptr, "%i", &(f->normals[i]));
        f->normals[i]--;
    }
}


void read_model(model *const m, const char *file_name) {
    FILE *file_ptr;

    if (!(file_ptr = fopen(file_name, "r"))) {
        fprintf(stderr, "can't read file");
        exit(1);
    }

    m->n_vertices = count_char(file_ptr, 'v');
    m->n_faces = count_char(file_ptr, 'f');

    m->vertices = calloc(m->n_vertices, sizeof *(m->vertices));
    m->faces = calloc(m->n_faces, sizeof *(m->faces));

    if (!(m->vertices) || !(m->faces)) {
        fprintf(stderr, "can't allocate memory\n");
        exit(1);
    }

    rewind(file_ptr);

    char c;
    int vertex_i = 0;
    int face_i = 0;
    float x, y, z;

    while ((c = getc(file_ptr)) != EOF) {
        if (c == 'v') {
            c = getc(file_ptr);

            if (c == EOF)
                break;

            if (c == ' ') {
                fscanf(file_ptr, "%f %f %f", &x, &y, &z);
                
                m->vertices[vertex_i] = (vec3f) {
                    .x = x,
                    .y = y,
                    .z = z
                };

                vertex_i++;
            }
        } else if (c == 'f') {
            c = getc(file_ptr);

            if (c == EOF)
                break;

            if (c == ' ') {
                read_face(file_ptr, &(m->faces[face_i]));

                face_i++;
            }
        }    
    }

    fclose(file_ptr);
}


void free_model(model *const m) {
    free(m->vertices);
    
    for (int i = 0; i < m->n_faces; i++) {
        free_face(&(m->faces[i]));
    }

    free(m->faces);
}
