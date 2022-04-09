#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "geometry.h"


float determinant_2x2(const float a, const float b, 
                      const float c, const float d) {
    return a * d - b * c;
}


vec3f vec3f_add(const vec3f *const u, const vec3f *const v) {
    return (vec3f) {
        .x0 = u->x0,
        .y0 = u->y0,
        .z0 = u->z0,
        .x = u->x + v->x,
        .y = u->y + v->y,
        .z = u->z + v->z
    };
}


vec3f vec3f_sub(const vec3f *const u, const vec3f *const v) {
    return (vec3f) {
        .x0 = u->x0,
        .y0 = u->y0,
        .z0 = u->z0,
        .x = u->x - v->x,
        .y = u->y - v->y,
        .z = u->z - v->z
    };
}


vec3f vec3f_mul(const vec3f *const u, const float c) {
    return (vec3f) {
        .x0 = u->x0,
        .y0 = u->y0,
        .z0 = u->z0,
        .x = c * u->x,
        .y = c * u->y,
        .z = c * u->z
    };
}


float vec3f_scalar(const vec3f *const u, const vec3f *const v) {
    return u->x * v->x + u->y * v->y + u->z * v->z;
}


float vec3f_norm(const vec3f *const u) {
    return sqrt(vec3f_scalar(u, u));
}


vec3f vec3f_normalize(const vec3f *const u) {
    float norm = vec3f_norm(u);

    if (norm == 0) {
        fprintf(stderr, "division by 0\n");
        exit(1);
    }

    return (vec3f) {
        .x0 = u->x0,
        .y0 = u->y0,
        .z0 = u->z0,
        .x = u->x / norm,
        .y = u->y / norm,
        .z = u->z / norm
    };
}


vec3f vec3f_cross(const vec3f *const u, const vec3f *const v) {
    return (vec3f) {
        .x0 = u->x0,
        .y0 = u->y0,
        .z0 = u->z0,
        .x = determinant_2x2(u->y, u->z, v->y, v->z),
        .y = determinant_2x2(u->z, u->x, v->z, v->x),
        .z = determinant_2x2(u->x, u->y, v->x, v->y) 
    };
}
