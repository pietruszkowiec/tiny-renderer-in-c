#ifndef GEOMETRY_H
#define GEOMETRY_H


float determinant_2x2(const float a, const float b,
                      const float c, const float d);


typedef struct {
    float x0, y0, z0;
    float x, y, z;
} vec3f;

vec3f vec3f_add(const vec3f *const u, const vec3f *const v);
vec3f vec3f_sub(const vec3f *const u, const vec3f *const v);
vec3f vec3f_mul(const vec3f *const u, const float c);
float vec3f_scalar(const vec3f *const u, const vec3f *const v);
float vec3f_norm(const vec3f *const u);
vec3f vec3f_normalize(const vec3f *const u);
vec3f vec3f_cross(const vec3f *const u, const vec3f *const v);


#endif // GEOMETRY_H
