#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>

#include "stack.h"

typedef struct gls_Vec3f
{
	float x, y, z;
} gls_Vec3f;

typedef struct gls_Camera
{
	gls_Vec3f pos, rot;
} gls_Camera;

typedef struct gls_State
{
	gls_Vec3f origin;
	gls_Vec3f translate;
	gls_Vec3f rotate;
	gls_Vec3f scale;
	gls_Vec3f color;
} gls_State;

extern gls_Camera _gls_camera;
extern gls_Stack _gls_state;
extern gls_Stack _gls_verts;
extern GLuint _gls_vao;
extern GLuint _gls_vbo;
extern uint32_t _gls_width;
extern uint32_t _gls_height;
extern GLuint _gls_shader;
extern float _gls_fov;
extern float _gls_near;
extern float _gls_far;

gls_Vec3f gls_vec3f_add(gls_Vec3f left, gls_Vec3f right);
gls_Vec3f gls_vec3f_sub(gls_Vec3f left, gls_Vec3f right);
gls_Vec3f gls_vec3f_mul(gls_Vec3f left, gls_Vec3f right);
gls_Vec3f gls_vec3f_div(gls_Vec3f left, gls_Vec3f right);
gls_Vec3f gls_vec3f_abs(gls_Vec3f vec);
gls_Vec3f gls_vec3f(float x, float y, float z);
gls_Vec3f gls_vec3f1(float x);

float gls_toRad(float deg);
float gls_toDeg(float rad);
float gls_wrapDeg(float deg);

void gls_init();
void gls_delete();

void gls_begin(float x, float y, float z, float rx, float ry, float rz);
void gls_pushState();
void gls_popState();
gls_State* gls_getState();
gls_State* gls_getStateIndex(uint64_t index);
void gls_draw(bool clear);

void gls_origin(float x, float y, float z);
void gls_translate(float x, float y, float z);
void gls_rotate(float x, float y, float z);
void gls_scale(float x, float y, float z);
void gls_colorRGB(float r, float g, float b);
void gls_colorHSV(float h, float s, float v);
gls_Vec3f gls_colorRGBtoHSV(float r, float g, float b);
gls_Vec3f gls_colorHSVtoRGB(float h, float s, float v);
void gls_vertex(float x, float y, float z);

gls_Vec3f gls_applyTrans(float x, float y, float z);
void gls_setMatrix();
gls_Vec3f gls_normalize(gls_Vec3f vec);
gls_Vec3f gls_cross(gls_Vec3f x, gls_Vec3f y);
float gls_dot(gls_Vec3f x, gls_Vec3f y);

void gls_setViewport(uint32_t width, uint32_t height);
void gls_setFOV(float fov);
void gls_setNearFar(float near, float far);
void gls_setWireframe(bool state);
void gls_setFrontFace(bool ccw);