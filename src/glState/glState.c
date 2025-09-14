#include "glState.h"

gls_Camera _gls_camera = { 0 };
gls_Stack _gls_state = { 0 };
gls_Stack _gls_verts = { 0 };
GLuint _gls_vao = 0;
GLuint _gls_vbo = 0;
uint32_t _gls_width = 0;
uint32_t _gls_height = 0;
GLuint _gls_shader = 0;


void gls_vec3f_add(gls_Vec3f* left, gls_Vec3f right)
{
	left->x += right.x;
	left->y += right.y;
	left->z += right.z;
}

void gls_vec3f_sub(gls_Vec3f* left, gls_Vec3f right)
{
	left->x -= right.x;
	left->y -= right.y;
	left->z -= right.z;
}

void gls_vec3f_mul(gls_Vec3f* left, gls_Vec3f right)
{
	left->x *= right.x;
	left->y *= right.y;
	left->z *= right.z;
}

void gls_vec3f_div(gls_Vec3f* left, gls_Vec3f right)
{
	left->x /= right.x;
	left->y /= right.y;
	left->z /= right.z;
}


gls_Vec3f gls_vec3f(float x, float y, float z)
{
	gls_Vec3f vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return vec;
}

float gls_toRad(float deg)
{
	return deg / 180.f * 3.1415f;
}

float gls_toDeg(float rad)
{
	return rad / 3.1415f * 180.f;
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
	stack_init(&_gls_verts, sizeof(gls_Vec3f), 128);

	_gls_state.length = 1;
	gls_pushState();

	glEnable(GL_CULL_FACE);
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
	state.color = gls_vec3f(1, 1, 1);
	stack_push(&_gls_state, &state);
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

	gls_Vec3f vec = { r, g, b };
	gls_getState()->color = vec;
}


void gls_vertex(float x, float y, float z)
{
	gls_Vec3f p = gls_applyTrans(x, y, z);

	gls_Vec3f vec = gls_project(p);

	stack_push(&_gls_verts, &vec);

	stack_push(&_gls_verts, &gls_getState()->color);

	if (_gls_verts.length % 6 == 0)
	{
		gls_Vec3f* ptr = stack_index(&_gls_verts, _gls_verts.length - 6);
		if (ptr[0].z < 0 || ptr[2].z < 0 || ptr[4].z < 0)
			_gls_verts.length -= 6;
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
	// - rotates 180deg in all axises every iteration
	// - z origin does nothing

	gls_Vec3f point = { x, y, z };

	for (uint64_t i = _gls_state.length - 1; i > 0; i--)
	{
		float angle, angle3d, dist, dist3d;

		gls_vec3f_add(&point, gls_getStateIndex(i)->translate);
		gls_vec3f_mul(&point, gls_getStateIndex(i)->scale);

		angle = gls_toDeg(atan2f(gls_getStateIndex(i)->origin.x - point.x,
			gls_getStateIndex(i)->origin.z - point.z));
		 dist = sqrtf(powf(gls_getStateIndex(i)->origin.x - point.x, 2) + 
			 powf(gls_getStateIndex(i)->origin.z - point.z, 2));
		point.x = dist * sinf(gls_toRad(angle + gls_getStateIndex(i)->rotate.y));
		point.z = dist * cosf(gls_toRad(angle + gls_getStateIndex(i)->rotate.y));

		angle3d = gls_toDeg(atan2f(gls_getStateIndex(i)->origin.y - point.y,
			gls_getStateIndex(i)->origin.z - point.z));
		dist3d = sqrtf(powf(gls_getStateIndex(i)->origin.y - point.y, 2) + 
			powf(gls_getStateIndex(i)->origin.z - point.z, 2));
		point.y = -dist3d * sinf(gls_toRad(angle3d + gls_getStateIndex(i)->rotate.x));
		point.z = -dist3d * cosf(gls_toRad(angle3d + gls_getStateIndex(i)->rotate.x));
	}

	gls_vec3f_sub(&point, _gls_camera.pos);

	return point;
}

gls_Vec3f gls_project(gls_Vec3f p)
{
	gls_Vec3f s = {
		sinf(gls_toRad(_gls_camera.rot.x)),
		sinf(gls_toRad(_gls_camera.rot.y)),
		sinf(gls_toRad(_gls_camera.rot.z)) };
	gls_Vec3f c = {
		cosf(gls_toRad(_gls_camera.rot.x)),
		cosf(gls_toRad(_gls_camera.rot.y)),
		cosf(gls_toRad(_gls_camera.rot.z)) };
	gls_Vec3f d = {
		c.y * (s.z * p.y + c.z * p.x) - s.y * p.z,
		s.x * (c.y * p.z + s.y * (s.z * p.y + c.z * p.x)) + c.x * (c.z * p.y - s.z * p.x),
		c.x * (c.y * p.z + s.y * (s.z * p.y + c.z * p.x)) - s.x * (c.z * p.y - s.z * p.x) };

	float bx = d.x * 1000.f / (d.z * _gls_width);
	float by = d.y * 1000.f / (d.z * _gls_height);

	return gls_vec3f(bx, by, d.z / 1000.f);

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

void gls_setViewport(uint32_t width, uint32_t height)
{
	glViewport(0, 0, width, height);
	_gls_width = width;
	_gls_height = height;
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

	if (clear)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(_gls_vao);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(3 * _gls_verts.length));
}
