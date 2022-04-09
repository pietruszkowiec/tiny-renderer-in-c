#include <stdio.h>
#include <stdlib.h>

#include "wireframe.h"
#include "tgaimage.h"
#include "model.h"


void swap(int *a, int *b) {
    *a = (*a) ^ (*b);
    *b = (*a) ^ (*b);
    *a = (*b) ^ (*a);
}


void draw_line(tga_image *const image, const tga_pixel *const pixel,
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


void draw_wireframe(tga_image *const image, const char *file_name, 
                    AXIS axis, int width, int height) {
    model m;
    read_model(&m, file_name);

    printf("n_vertices = %i, n_faces = %i\n", m.n_vertices, m.n_faces);

    tga_pixel white = (tga_pixel) {
        .r = 255, 
        .g = 255,
        .b = 255
    };

    float min_x, min_y, min_z, max_x, max_y, max_z;
    min_x = m.vertices[0].x;
    min_y = m.vertices[0].y;
    min_z = m.vertices[0].z;
    max_x = min_x;
    max_y = min_y;
    max_z = min_z;

    for (int i = 1; i < m.n_vertices; i++) {
        min_x = MIN(min_x, m.vertices[i].x);
        min_y = MIN(min_y, m.vertices[i].y);
        min_z = MIN(min_z, m.vertices[i].z);
        max_x = MAX(max_x, m.vertices[i].x);
        max_y = MAX(max_y, m.vertices[i].y);
        max_z = MAX(max_z, m.vertices[i].z);
    }

    float min, max;
    switch (axis) {
        case XY:
            min = MIN(min_x, min_y);
            max = MAX(max_x, max_y);
            break;
        case XZ:
            min = MIN(min_x, min_z);
            max = MAX(max_x, max_z);
            break;
        case YZ:
            min = MIN(min_y, min_z);
            max = MAX(max_y, max_z);
            break;
    }
    
    const float image_zoom = 1.1;

    float x_scale, y_scale;
    x_scale = width / (max - min) / image_zoom;
    y_scale = height / (max - min) / image_zoom;

    float scale_offset = 0.5 * (1 - 1 / image_zoom);

    face f;
    vec3f u, v;
    int x0, y0, x1, y1;


    for (int i = 0; i < m.n_faces; i++) {
        f = m.faces[i];

        for (int j = 0; j < f.n_vertices; j++) {
            u = m.vertices[f.vertices[j]];
            v = m.vertices[f.vertices[(j + 1) % f.n_vertices]];

            switch (axis) {
                case XY:
                    x0 = (u.x - min) * x_scale + scale_offset;
                    y0 = (u.y - min) * y_scale + scale_offset;
                    x1 = (v.x - min) * x_scale + scale_offset;
                    y1 = (v.y - min) * y_scale + scale_offset;
                    break;
                case XZ:
                    x0 = (u.x - min) * x_scale + scale_offset;
                    y0 = (u.z - min) * y_scale + scale_offset;
                    x1 = (v.x - min) * x_scale + scale_offset;
                    y1 = (v.z - min) * y_scale + scale_offset;
                    break;
                case YZ:
                    x0 = (u.y - min) * x_scale + scale_offset;
                    y0 = (u.z - min) * y_scale + scale_offset;
                    x1 = (v.y - min) * x_scale + scale_offset;
                    y1 = (v.z - min) * y_scale + scale_offset;
                    break;
            }
            
            draw_line(image, &white, x0, y0, x1, y1);
        }
    }

    free_model(&m);
}
