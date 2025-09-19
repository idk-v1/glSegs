#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include <GLFW/util/darkTheme.h>
#include <GLFW/util/sleep.h>

#include "../glState/glState.h"
#include "../objReader/objReader.h"

typedef struct Creature
{
	gls_Vec3f pos;
	gls_Vec3f vel;
	gls_Vec3f rot;
	gls_Vec3f acc;
	int health;
	float moveSpeed;
} Creature;

typedef struct Game
{
	GLFWwindow* window;
	int screenW, screenH;

	float lookSpeed;
	float fov;

	bool pauseState;
	bool escLast;

	bool isOpen;

	double lastTime;
	double deltaTime;
	uint64_t ticks;

	Creature player;

	gls_Stack paraVerts;
} Game;

Game game_init(int width, int height, const char* title);
void game_delete(Game* game);

void game_update(Game* game);

void game_playerInput(Game* game);

void game_draw(Game* game);

void game_drawModel(Game* game, gls_Stack* verts);

void game_setTitle(Game* game, char* fmt, ...);