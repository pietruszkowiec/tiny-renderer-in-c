#include <stdio.h>
#include <stdlib.h>

#include "tgaimage.h"
#include "model.h"


void swap(int *a, int *b) {
    *a = (*a) ^ (*b);
    *b = (*a) ^ (*b);
    *a = (*b) ^ (*a);
}


void draw_line(tga_image *const image, tga_pixel *const pixel,
             int x0, int y0, int x1, int y1) { 
    int steep = 0;
    if (abs(x0 - x1) < abs(y0 - y1)) {
        swap(&x0, &y0);
        swap(&x1, &y1);
        steep = 1;
    }
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = y0; 
    for (int x = x0; x <= x1; x++) {
        if (steep)
            set_tga_pixel(image, pixel, y, x);
        else
            set_tga_pixel(image, pixel, x, y);
        
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0) ? 1 : -1;
            error2 -= dx * 2;
        }
    } 
}


int main(void) {
    model m;

    read_model(&m, "test.obj");

    printf("n_vertices = %i, n_faces = %i\n", m.n_vertices, m.n_faces);

    for (int i = 0; i < m.n_vertices; i++) {
        printf("v %f %f %f\n", m.vertices[i].x, 
                               m.vertices[i].y, 
                               m.vertices[i].z);
    }

    for (int i = 0; i < m.n_faces; i++) {
        printf("f ");

        for (int j = 0; j < 3; j++) {
            printf("%i/%i/%i ", m.faces[i].vertices[j], 
                                m.faces[i].textures[j], 
                                m.faces[i].normals[j]);
        }

        putchar('\n');
    }

    free_model(&m);

    return 0;
}
