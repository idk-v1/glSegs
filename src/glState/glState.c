#include "glState.h"

gls_Camera _gls_camera = { 0 };
gls_Stack _gls_state = { 0 };
gls_Stack _gls_verts = { 0 };
gls_Stack _gls_lights = { 0 };
GLuint _gls_vao = 0;
GLuint _gls_vbo = 0;
uint32_t _gls_width = 0;
uint32_t _gls_height = 0;
GLuint _gls_shader = 0;
float _gls_fov = 75.f;
float _gls_near = 0.1f;
float _gls_far = 1000.f;


gls_Vec3f gls_vec3f_add(gls_Vec3f left, gls_Vec3f right)
{
	gls_Vec3f vec;
	vec.x = left.x + right.x;
	vec.y = left.y + right.y;
	vec.z = left.z + right.z;
	return vec;
}

gls_Vec3f gls_vec3f_sub(gls_Vec3f left, gls_Vec3f right)
{
	gls_Vec3f vec;
	vec.x = left.x - right.x;
	vec.y = left.y - right.y;
	vec.z = left.z - right.z;
	return vec;
}

gls_Vec3f gls_vec3f_mul(gls_Vec3f left, gls_Vec3f right)
{
	gls_Vec3f vec;
	vec.x = left.x * right.x;
	vec.y = left.y * right.y;
	vec.z = left.z * right.z;
	return vec;
}

gls_Vec3f gls_vec3f_div(gls_Vec3f left, gls_Vec3f right)
{
	gls_Vec3f vec;
	vec.x = left.x / right.x;
	vec.y = left.y / right.y;
	vec.z = left.z / right.z;
	return vec;
}

gls_Vec3f gls_vec3f_abs(gls_Vec3f vec)
{
	vec.x = fabsf(vec.x);
	vec.y = fabsf(vec.y);
	vec.z = fabsf(vec.z);
	return vec;
}

gls_Vec3f gls_vec3f(float x, float y, float z)
{
	gls_Vec3f vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

gls_Vec3f gls_vec3f1(float x)
{
	return gls_vec3f(x, x, x);
}


float gls_toRad(float deg)
{
	const float toRad = 3.1415f / 180.f;
	return deg * toRad;
}

float gls_toDeg(float rad)
{
	const float toDeg = 180.f / 3.1415f;
	return rad * toDeg;
}

float gls_wrapDeg(float deg)
{
	deg = fmodf(deg, 360.f);
	if (deg < 0)
		deg += 360.f;
	return deg;
}


void gls_init()
{
	stack_init(&_gls_state, sizeof(gls_State), 32);
	stack_init(&_gls_verts, sizeof(gls_Vec3f), 65536 * 6);
	stack_init(&_gls_lights, sizeof(gls_Light), 16);

	_gls_state.length = 1;
	gls_getStateIndex(0)->color = gls_vec3f(1.f, 1.f, 1.f);
	gls_pushState();

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	static const char* vertShaderSrc =
#include "shader.vert"

	static const char* fragShaderSrc =
#include "shader.frag"


	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);


	_gls_shader = glCreateProgram();
	glAttachShader(_gls_shader, vertShader);
	glAttachShader(_gls_shader, fragShader);

	glBindAttribLocation(_gls_shader, 0, "aPos");
	glBindAttribLocation(_gls_shader, 1, "aColor");

	glLinkProgram(_gls_shader);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	_gls_camera.pos = gls_vec3f(0, 0, 0);
	_gls_camera.rot = gls_vec3f(0, 0, 0);
}

void gls_delete()
{
	stack_free(&_gls_state);
	stack_free(&_gls_verts);
	stack_free(&_gls_lights);

	if (_gls_vao)
		glDeleteVertexArrays(1, &_gls_vao);
	if (_gls_vbo)
		glDeleteBuffers(1, &_gls_vbo);

	if (_gls_shader)
		glDeleteProgram(_gls_shader);
}


void gls_begin(float x, float y, float z, float rx, float ry, float rz)
{
	if (_gls_vao)
		glDeleteVertexArrays(1, &_gls_vao);
	if (_gls_vbo)
		glDeleteBuffers(1, &_gls_vbo);
	_gls_vao = _gls_vbo = 0;
	
	_gls_state.length = 1;
	_gls_verts.length = 0;
	gls_pushState();

	_gls_camera.pos = gls_vec3f(x, y, z);
	_gls_camera.rot = gls_vec3f(rx, ry, rz);
}

void gls_pushState()
{
	gls_State state = { 0 };
	state.scale = gls_vec3f(1, 1, 1);
	state.color = gls_getState()->color;
	stack_push(&_gls_state, &state);
}

void gls_popState()
{
	if (_gls_state.length > 1)
		stack_pop(&_gls_state);
}

gls_State* gls_getState()
{
	return stack_last(&_gls_state);
}

gls_State* gls_getStateIndex(uint64_t index)
{
	return stack_index(&_gls_state, index);
}

void gls_draw(bool clear)
{
	glGenBuffers(1, &_gls_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _gls_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		_gls_verts.length * _gls_verts.elemSize,
		_gls_verts.data, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &_gls_vao);
	glBindVertexArray(_gls_vao);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(gls_Vec3f), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(gls_Vec3f), (void*)sizeof(gls_Vec3f));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glUseProgram(_gls_shader);

	gls_setMatrix();

	if (clear)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(_gls_vao);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(3 * _gls_verts.length));
}


void gls_origin(float x, float y, float z)
{
	gls_Vec3f vec = { x, y, z };
	gls_getState()->origin = vec;
}

void gls_translate(float x, float y, float z)
{
	gls_Vec3f vec = { x, y, z };
	gls_getState()->translate = vec;
}

void gls_rotate(float x, float y, float z)
{
	gls_Vec3f vec = { x, y, z };
	gls_getState()->rotate = vec;
}

void gls_scale(float x, float y, float z)
{
	gls_Vec3f vec = { x, y, z };
	gls_getState()->scale = vec;
}

void gls_colorRGB(float r, float g, float b)
{
	gls_Vec3f vec = { r, g, b };
	if (r > 1.f)
		r = 1.f;
	if (r < 0.f)
		r = 0.f;
	if (g > 1.f)
		g = 1.f;
	if (g < 0.f)
		g = 0.f;
	if (b > 1.f)
		b = 1.f;
	if (b < 0.f)
		b = 0.f;
	gls_getState()->color = vec;
}

void gls_colorHSV(float h, float s, float v)
{
	gls_getState()->color = gls_colorHSVtoRGB(h, s, v);
}

gls_Vec3f gls_colorRGBtoHSV(float r, float g, float b)
{
	gls_Vec3f hsv = { 0.f };

	float fCMax = max(max(r, g), b);
	float fCMin = min(min(r, g), b);
	float fDelta = fCMax - fCMin;

	if (fDelta > 0.f)
	{
		if (fCMax == r)
		{
			hsv.x = 60.f * (fmodf(((g - b) / fDelta), 6.f));
		}
		else if (fCMax == g)
		{
			hsv.x = 60.f * (((b - r) / fDelta) + 2.f);
		}
		else if (fCMax == b)
		{
			hsv.x = 60.f * (((r - g) / fDelta) + 4.f);
		}

		if (fCMax > 0.f)
		{
			hsv.y = fDelta / fCMax;
		}
		else
		{
			hsv.y = 0.f;
		}

		hsv.z = fCMax;
	}
	else
	{
		hsv.x = 0.f;
		hsv.y = 0.f;
		hsv.z = fCMax;
	}

	if (hsv.x < 0.f)
		hsv.x += 360.f;

	hsv.x /= 360.f;
	return hsv;
}

gls_Vec3f gls_colorHSVtoRGB(float h, float s, float v)
{
	float r = 0, g = 0, b = 0;

	if (h < 0)
		h = 360.f - fmodf(-h, 360.f);
	else
		h = fmodf(h, 360.f);

	int i = (int)(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (abs(i) % 6)
	{
	case 0: r = v, g = t, b = p; break;
	case 1: r = q, g = v, b = p; break;
	case 2: r = p, g = v, b = t; break;
	case 3: r = p, g = q, b = v; break;
	case 4: r = t, g = p, b = v; break;
	case 5: r = v, g = p, b = q; break;
	}

	return gls_vec3f(r, g, b);
}

void gls_vertex(float x, float y, float z)
{
	gls_Vec3f point = gls_applyTrans(x, y, z);

	stack_push(&_gls_verts, &point);

	stack_push(&_gls_verts, &gls_getState()->color);

	if (_gls_verts.length % 6 == 0) // full triangle
	{
		gls_applyLighting(stack_index(&_gls_verts, _gls_verts.length - 6));
	}
}


void gls_applyLighting(gls_Vec3f* triPtr)
{
	// TODO:
	// 1. no lighting colors
	// 2. lighting not additives
	// 3. no ambient mode
	// 4. no spotlight mode

	gls_Vec3f tri[6];
	for (int i = 0; i < 6; i++)
	{
		tri[i] = triPtr[i];
		if (i % 2 == 0)
			tri[i] = gls_vec3f_add(tri[i], _gls_camera.pos);
	}

	gls_Vec3f u = gls_vec3f_sub(tri[2], tri[0]);
	gls_Vec3f v = gls_vec3f_sub(tri[4], tri[0]);

	gls_Vec3f norm = { 0 };
	norm.x = u.y * v.z - u.z * v.y;
	norm.y = u.z * v.x - u.x * v.z;
	norm.z = u.x * v.y - u.y * v.x;
	norm = gls_normalize(norm);

	gls_Vec3f avg = gls_vec3f_add(gls_vec3f_add(tri[0], tri[2]), tri[4]);
	avg = gls_vec3f_div(avg, gls_vec3f1(3.f));


	for (uint64_t i = 0; i < _gls_lights.length; i++)
	{
		gls_Light* light = stack_index(&_gls_lights, i);
		switch (light->type)
		{
		case 0: // ambient
		{
			break;
		}
		case 1: // global
		{
			gls_Vec3f lightNorm = gls_normalize(gls_vec3f(
				-sinf(gls_toRad(light->rot.y)) * cosf(gls_toRad(light->rot.x)),
				sinf(gls_toRad(light->rot.x)),
				-cosf(gls_toRad(light->rot.y)) * cosf(gls_toRad(light->rot.x))));

			gls_Vec3f normDiffVec = gls_vec3f_sub(norm, lightNorm);
			float normDiff = gls_sqrt(normDiffVec.x * normDiffVec.x +
				normDiffVec.y * normDiffVec.y + normDiffVec.z * normDiffVec.z) / 2.f;

			gls_Vec3f color = gls_colorRGBtoHSV(tri[1].x, tri[1].y, tri[1].z);
			triPtr[1] = gls_colorHSVtoRGB(color.x, color.y, color.z * (1.f - normDiff));
			color = gls_colorRGBtoHSV(tri[3].x, tri[3].y, tri[3].z);
			triPtr[3] = gls_colorHSVtoRGB(color.x, color.y, color.z * (1.f - normDiff));
			color = gls_colorRGBtoHSV(tri[5].x, tri[5].y, tri[5].z);
			triPtr[5] = gls_colorHSVtoRGB(color.x, color.y, color.z * (1.f - normDiff));

			break;
		}
		case 2: // point
		{
			// Point lighting
			gls_Vec3f lightPos = light->pos;
			gls_Vec3f lightNorm = gls_normalize(gls_vec3f_sub(lightPos, avg));

			gls_Vec3f normDiffVec = gls_vec3f_sub(norm, lightNorm);
			float normDiff = gls_sqrt(normDiffVec.x * normDiffVec.x +
				normDiffVec.y * normDiffVec.y + normDiffVec.z * normDiffVec.z) / 2.f;

			gls_Vec3f distVec = gls_vec3f_sub(lightPos, avg);
			float dist = gls_sqrt(distVec.x * distVec.x +
				distVec.y * distVec.y + distVec.z * distVec.z);

			float strength;
			if (light->strength <= 0)
				strength = 0;
			else if (light->strength == INFINITY)
				strength = 1.f;
			else
				strength = (light->strength - dist) / light->strength;

			gls_Vec3f color = gls_colorRGBtoHSV(tri[1].x, tri[1].y, tri[1].z);
			triPtr[1] = gls_colorHSVtoRGB(color.x, color.y, color.z * (strength - normDiff));
			color = gls_colorRGBtoHSV(tri[3].x, tri[3].y, tri[3].z);
			triPtr[3] = gls_colorHSVtoRGB(color.x, color.y, color.z * (strength - normDiff));
			color = gls_colorRGBtoHSV(tri[5].x, tri[5].y, tri[5].z);
			triPtr[5] = gls_colorHSVtoRGB(color.x, color.y, color.z * (strength - normDiff));
			break;
		}
		case 3: // spotlight
		{
			break;
		}
		}
	}
}

gls_Vec3f gls_applyTrans(float x, float y, float z)
{
	// origin by itself is just translate
	//
	// translate happens before rotation
	// rotation rotates all points around origin
	// camera position is removed from points

	// BUGS:
	//  - Rotating on both axises produces a pringle orbit

	gls_Vec3f point = { x, y, z };

	for (uint64_t i = _gls_state.length - 1; i > 0; i--)
	{
		point = gls_vec3f_add(point, gls_getStateIndex(i)->translate);
		point = gls_vec3f_mul(point, gls_getStateIndex(i)->scale);

		float angleY = gls_toDeg(gls_atan2(point.x, point.z)) + gls_getStateIndex(i)->rotate.y;
		float distXZ = gls_sqrt(gls_pow2(point.x) + gls_pow2(point.z));
		point.x = distXZ * sinf(gls_toRad(angleY));
		point.z = distXZ * cosf(gls_toRad(angleY));

		float angleX = gls_toDeg(gls_atan2(point.y, point.z)) + gls_getStateIndex(i)->rotate.x;
		float distYZ = gls_sqrt(gls_pow2(point.y) + gls_pow2(point.z));
		point.y = distYZ * sinf(gls_toRad(angleX));
		point.z = distYZ * cosf(gls_toRad(angleX));

		point = gls_vec3f_add(point, gls_getStateIndex(i)->origin);
	}

	return gls_vec3f_sub(point, _gls_camera.pos);
}

void gls_setMatrix()
{
	float aspect = (float)_gls_width / (float)_gls_height;
	float proj[4 * 4] = { 0 };
	proj[0 + 0 * 4] = 1.f / (aspect * tanf(gls_toRad(_gls_fov) / 2.f));
	proj[1 + 1 * 4] = 1.f / tanf(gls_toRad(_gls_fov) / 2.f);
	proj[2 + 2 * 4] = -(_gls_far + _gls_near) / (_gls_far - _gls_near);
	proj[2 + 3 * 4] = -1;
	proj[3 + 2 * 4] = -(2.f * _gls_far * _gls_near) / (_gls_far - _gls_near);

	glUniformMatrix4fv(glGetUniformLocation(_gls_shader, "proj"), 1, true, proj);

	gls_Vec3f up = { 0.f, 1.f, 0.f };
	gls_Vec3f lookat = gls_normalize(gls_vec3f(
		-sinf(gls_toRad(_gls_camera.rot.y)) * cosf(gls_toRad(_gls_camera.rot.x)),
		sinf(gls_toRad(_gls_camera.rot.x)),
		-cosf(gls_toRad(_gls_camera.rot.y)) * cosf(gls_toRad(_gls_camera.rot.x))));
	gls_Vec3f s = gls_normalize(gls_cross(lookat, up));
	gls_Vec3f u = gls_cross(s, lookat);
	float view[4 * 4] = { 0 };
	view[0 + 0 * 4] = s.x;
	view[1 + 0 * 4] = s.y;
	view[2 + 0 * 4] = s.z;
	view[0 + 1 * 4] = u.x;
	view[1 + 1 * 4] = u.y;
	view[2 + 1 * 4] = u.z;
	view[0 + 2 * 4] = -lookat.x;
	view[1 + 2 * 4] = -lookat.y;
	view[2 + 2 * 4] = -lookat.z;
	view[3 + 0 * 4] = -gls_dot(s, lookat);
	view[3 + 1 * 4] = -gls_dot(u, lookat);
	view[3 + 2 * 4] = gls_dot(lookat, lookat);
	view[3 + 3 * 4] = 1.f;

	glUniformMatrix4fv(glGetUniformLocation(_gls_shader, "view"), 1, true, view);
}

gls_Vec3f gls_normalize(gls_Vec3f vec)
{
	float dist = gls_sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= dist;
	vec.y /= dist;
	vec.z /= dist;
	return vec;
}

gls_Vec3f gls_cross(gls_Vec3f x, gls_Vec3f y)
{
	gls_Vec3f vec = { 0 };
	vec.x = x.y * y.z - y.y * x.z;
	vec.y = x.z * y.x - y.z * x.x;
	vec.z = x.x * y.y - y.x * x.y;
	return vec;
}

float gls_dot(gls_Vec3f x, gls_Vec3f y)
{
	gls_Vec3f vec = gls_vec3f_mul(x, y);
	return vec.x + vec.y + vec.z;
}

float gls_sqrt(float x)
{	
	union
	{
		int i;
		float x;
	} u;
	u.x = x;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

	// Two Babylonian Steps (simplified from:)
	// u.x = 0.5f * (u.x + x/u.x);
	// u.x = 0.5f * (u.x + x/u.x);
	u.x = u.x + x / u.x;
	u.x = 0.25f * u.x + x / u.x;

	return u.x;
}

float gls_atan2(float y, float x)
{
	//http://pubs.opengroup.org/onlinepubs/009695399/functions/atan2.html
	//Volkan SALMA

	const float ONEQTR_PI = 3.1415f / 4.f;
	const float THRQTR_PI = 3.f * 3.1415f / 4.f;
	float r, angle;
	float abs_y = fabsf(y) + 1e-10f;      // kludge to prevent 0/0 condition
	if (x < 0.0f)
	{
		r = (x + abs_y) / (abs_y - x);
		angle = THRQTR_PI;
	}
	else
	{
		r = (x - abs_y) / (x + abs_y);
		angle = ONEQTR_PI;
	}
	angle += (0.1963f * r * r - 0.9817f) * r;
	if (y < 0.0f)
		return(-angle);     // negate if in quad III or IV
	else
		return(angle);
}

float gls_pow2(float x)
{
	return x * x;
}


void gls_setWireframe(bool state)
{
	if (state)
	{
		glEnable(GL_POLYGON_OFFSET_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_POLYGON_OFFSET_LINE);
	}
}

void gls_setFrontFace(bool ccw)
{
	glFrontFace(ccw ? GL_CCW : GL_CW);
}

void gls_setViewport(uint32_t width, uint32_t height)
{
	glViewport(0, 0, width, height);
	_gls_width = width;
	_gls_height = height;
}

void gls_setFOV(float fov)
{
	_gls_fov = fov;
}

void gls_setNearFar(float near, float far)
{
	_gls_near = near;
	_gls_far = far;
}


void gls_addLight(float x, float y, float z, float rx, float ry, float rz, float strength, gls_Vec3f color, int type)
{
	gls_Light light;
	light.pos = gls_vec3f(x, y, z);
	light.rot = gls_vec3f(rx, ry, rz);
	light.strength = strength;
	light.color = color;
	light.type = type;
	stack_push(&_gls_lights, &light);
}

void gls_addAmbientLight(gls_Vec3f color)
{
	gls_addLight(0.f, 0.f, 0.f, 0.f, 0.f, 0.f, INFINITY, color, 0);
}

void gls_addGlobalLight(float rx, float ry, float rz, gls_Vec3f color)
{
	gls_addLight(0.f, 0.f, 0.f, rx, ry, rz, INFINITY, color, 1);
}

void gls_addPointLight(float x, float y, float z, float strength, gls_Vec3f color)
{
	gls_addLight(x, y, z, 0.f, 0.f, 0.f, strength, color, 2);
}

void gls_addSpotLight(float x, float y, float z, float rx, float ry, float rz, float strength, gls_Vec3f color)
{
	gls_addLight(x, y, z, rx, ry, rz, strength, color, 3);
}
