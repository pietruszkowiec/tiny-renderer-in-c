#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "geometry.h"


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


void read_face(FILE *file_ptr, face *const f) {
    char c;

    for (int i = 0; i < 3; i++) {
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
        printf("can't read file");
        exit(-1);
    }

    m->n_vertices = count_char(file_ptr, 'v');
    m->n_faces = count_char(file_ptr, 'f');

    m->vertices = (vec3f *) malloc(m->n_vertices * sizeof(vec3f));
    m->faces = (face *) malloc(m->n_faces * sizeof(face));

    if (!(m->vertices) || !(m->faces)) {
        printf("can't allocate memory\n");
        exit(-1);
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
    free(m->faces);
}
