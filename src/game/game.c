#include "game.h"


void drawRect(float xs, float ys, float zs)
{
	gls_Vec3f color = gls_colorRGBtoHSV(
		gls_getState()->color.x, gls_getState()->color.y, gls_getState()->color.z);

	// left
	gls_colorHSV(color.x, color.y, color.z - 0.0125f);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);

	// right
	gls_colorHSV(color.x, color.y, color.z - 0.0125f);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);

	// front
	gls_colorHSV(color.x, color.y, color.z);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);

	// back
	gls_colorHSV(color.x, color.y, color.z);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);

	// bottom
	gls_colorHSV(color.x, color.y, color.z - 0.1f);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);

	// top
	gls_colorHSV(color.x, color.y, color.z + 0.1f);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);

	gls_colorHSV(color.x, color.y, color.z);
}


void drawDino(float timer)
{
	gls_pushState(); // body
	gls_colorHSV(timer / 360.f, 1.f, 0.5f);
	drawRect(13.f, 13.f, 25.f);

	gls_pushState(); // body front
	gls_origin(0.f, 0.f, (25.f + 5.f) / 2.f);
	drawRect(5.f, 10.f, 5.f);

	gls_pushState(); // neck
	gls_origin(0.f, -1.f, 0.f);
	gls_translate(0.f, 0.f, 15.f / 2.f);
	gls_rotate(30.f + sinf(timer / 20.f) * 10.f, sinf(timer / 30.f) * 10.f, 0.f);
	drawRect(5.f, 8.f, 15.f);

	gls_pushState(); // neck upper
	gls_origin(0.f, 0.f, 15.f / 4.f);
	gls_translate(0.f, 0.f, 13.f / 2.f);
	gls_rotate(30.f + sinf(timer / 20.f) * 10.f, 0.f, 0.f);
	drawRect(5.f, 8.f, 13.f);

	gls_pushState(); // head
	gls_translate(0.f, -7.f / 2.f, 0.f);
	gls_origin(0.f, 0.f, (13.f + 13.f) / 2.f);
	gls_rotate(-90.f + sinf(timer / 20.f) * 10.f, 0.f, 0.f);
	drawRect(5.f, 7.f, 13.f);

	gls_pushState(); // upper jaw
	gls_origin(0.f, 1.5f, (13.f + 5.f) / 2.f);
	drawRect(5.f, 3.f, 5.f);
	gls_popState(); // upper jaw

	gls_pushState(); // lower jaw
	gls_origin(0.f, -1.5f, 13.f / 2.f);
	gls_translate(0.f, 0.f, 5.f / 2.f);
	gls_rotate(sinf(timer / 10.f) * 10.f, 0.f, 0.f);
	drawRect(5.f, 2.f, 5.f);
	gls_popState(); // lower jaw

	gls_pushState(); // crest start
	gls_origin(0.f, -2.f, -(13.f + 5.f) / 2.f + 4.5f);
	gls_rotate(60.f, 0.f, 0.f);
	drawRect(5.f, 10.f, 6.f);

	gls_pushState(); // crest
	gls_origin(0.f, 6.f / 2.f, 6.f / 2.f);
	gls_translate(0.f, 0.f, -10.f / 2.f);
	gls_rotate(-30.f, 0.f, 0.f);
	drawRect(5.f, 3.f, 10.f);

	gls_pushState(); // crest tip
	gls_origin(0.f, 0.f, -10.f / 2.f);
	gls_translate(0.f, 0.f, -7.f / 2.f);
	gls_rotate(20.f, 0.f, 0.f);
	drawRect(5.f, 2.f, 7.f);
	gls_popState(); // crest tip

	gls_popState(); // crest

	gls_popState(); // crest start

	gls_popState(); // head

	gls_popState(); // neck upper

	gls_popState(); // neck

	gls_popState(); // body front

	gls_pushState(); // body top
	gls_origin(0.f, 13.f / 2.f, 0.f);
	gls_translate(0.f, 2.f / 2.f, 0.f);
	drawRect(9.f, 2.f, 25.f);
	gls_popState(); // body top

	gls_pushState(); // body bottom
	gls_origin(0.f, -13.f / 2.f, 0.f);
	gls_translate(0.f, -2.f / 2.f, 0.f);
	drawRect(9.f, 2.f, 25.f);
	gls_popState(); // body bottom

	gls_pushState(); // body back
	gls_origin(0.f, 0.f, -25.f / 2.f);
	gls_translate(0.f, 0.f, -3.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(11.f, 11.f, 3.f);

	gls_pushState(); // body back top
	gls_origin(0.f, 11.f / 2.f, 0.f);
	gls_translate(0.f, 2.f / 2.f, 0.f);
	drawRect(8.f, 2.f, 3.f);
	gls_popState(); // body back top

	gls_pushState(); // body back bottom
	gls_origin(0.f, -11.f / 2.f, 0.f);
	gls_translate(0.f, -2.f / 2.f, 0.f);
	drawRect(8.f, 2.f, 3.f);
	gls_popState(); // body back bottom

	gls_pushState(); // body back 2
	gls_origin(0.f, 0.f, -3.f / 2.f);
	gls_translate(0.f, 0.f, -3.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(10.f, 13.f, 3.f);

	gls_pushState(); // body back 3
	gls_origin(0.f, 0.f, -3.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(9.f, 11.f, 4.f);

	gls_pushState(); // body back 4
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(8.f, 9.f, 4.f);

	gls_pushState(); // body back 5
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(6.f, 7.f, 4.f);

	gls_pushState(); // body back 6
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(4.f, 5.f, 4.f);

	gls_pushState(); // tail
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(3.f, 3.f, 4.f);

	gls_pushState(); // tail 2
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(3.f, 3.f, 4.f);

	gls_pushState(); // tail 3
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(2.f, 2.f, 4.f);

	gls_pushState(); // tail 4
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(2.f, 2.f, 4.f);

	gls_pushState(); // tail tip
	gls_origin(0.f, 0.f, -4.f / 2.f);
	gls_translate(0.f, 0.f, -4.f / 2.f);
	gls_rotate(cosf(timer / 20.f), sinf(timer / 20.f) * 10.f, 0.f);
	drawRect(1.f, 1.f, 6.f);

	gls_popState(); // tail tip

	gls_popState(); // tail 4

	gls_popState(); // tail 3

	gls_popState(); // tail 2

	gls_popState(); // tail

	gls_popState(); // body back 6

	gls_popState(); // body back 5

	gls_popState(); // body back 4

	gls_popState(); // body back 3

	gls_popState(); // body back 2

	gls_popState(); // body back

	gls_popState(); // body
}


Game game_init(int width, int height, const char* title)
{
	glfwInit();

	Game game = { 0 };

	game.screenW = width;
	game.screenH = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	game.window = glfwCreateWindow(game.screenW, game.screenH, title, NULL, NULL);
	if (game.window)
		game.isOpen = true;
	glfwSetWindowTheme(game.window, GLFW_THEME_AUTO);
	glfwMakeContextCurrent(game.window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(0);

	gls_setViewport(game.screenW, game.screenH);

	gls_init();
	game.fov = 90.f;
	game.lookSpeed = 0.25f;
	gls_setFOV(game.fov);
	gls_setNearFar(0.1f, 10000.f);

	game.player.moveSpeed = 0.75f;

	game.deltaTime = 0;
	game.lastTime = glfwGetTime();
	game.ticks = 0;
	game.pauseState = false;
	game.escLast = false;

	game.fps = 0;
	game.fpsCount = 0;
	game.lastFrameTime = glfwGetTime();
	game.deltaFrameTime = 0;

	glfwSetInputMode(game.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(game.window, game.screenW / 2.f, game.screenH / 2.f);

	game.paraVerts = obj_readVerts("para/lowpoly_parasaur.obj");
	//game.paraVerts = obj_readVerts("para/stegosaurus.obj");
	//game.paraVerts = obj_readVerts("para/trex.obj");

	return game;
}

void game_delete(Game* game)
{
	glfwDestroyWindow(game->window);
	stack_free(&game->paraVerts);

	memset(game, 0, sizeof(Game));

	glfwTerminate();
}

void game_update(Game* game)
{
	double time = glfwGetTime();
	game->deltaTime += time - game->lastTime;
	game->lastTime = time;

	int lastWidth = game->screenW;
	int lastHeight = game->screenH;
	glfwGetFramebufferSize(game->window, &game->screenW, &game->screenH);
	if (lastWidth != game->screenW || lastHeight != game->screenH)
		gls_setViewport(game->screenW, game->screenH);

	game_playerInput(game);

	if (!game->pauseState)
	{
		// update loop
		while (game->deltaTime >= 1.f / 60.f)
		{
			game->ticks++;
			game->deltaTime -= 1.f / 60.f;

			game->player.vel = gls_vec3f_add(game->player.vel, game->player.acc);
			game->player.vel = gls_vec3f_mul(game->player.vel, gls_vec3f1(0.8f));
			game->player.pos = gls_vec3f_add(game->player.pos, game->player.vel);
		}
	}

	//game_setTitle(game,
	//	"Pos(x, y, z): %1.f, %1.f, %1.f | Rot(x, y, z): %1.f, %1.f, %1.f",
	//	game->player.pos.x, game->player.pos.y, game->player.pos.z,
	//	game->player.rot.x, game->player.rot.y, game->player.rot.z);


	glfwPollEvents();

	game->isOpen = !glfwWindowShouldClose(game->window);

	_gls_lights.length = 0;
	//gls_addGlobalLight(0.f, 0.f, 0.f, gls_colorHSVtoRGB(0.67f, 1.f, 1.f));
	//gls_addGlobalLight(0.f, 0.f, 0.f, gls_colorHSVtoRGB(0.33f, 1.f, 1.f));
	//gls_addGlobalLight(0.f, 0.f, 0.f, gls_colorHSVtoRGB(0.f, 1.f, 1.f));
	gls_addPointLight(100.f * sinf(gls_toRad(0.f)), 50.f, 100.f * cosf(gls_toRad(0.f)), 
		200.f, gls_colorHSVtoRGB(0.f, 1.f, 1.f));
	gls_addPointLight(100.f * sinf(gls_toRad(120.f)), 50.f, 100.f * cosf(gls_toRad(120.f)), 
		200.f, gls_colorHSVtoRGB(0.33f, 1.f, 1.f));
	gls_addPointLight(100.f * sinf(gls_toRad(240.f)), 50.f, 100.f * cosf(gls_toRad(240.f)),
		200.f, gls_colorHSVtoRGB(0.67f, 1.f, 1.f));
	gls_addAmbientLight(gls_colorHSVtoRGB(0.f, 0.f, 0.05f));

	_gls_verts.length = 0;
	static int offset = 0;
	int dinoGrid = 4;
	for (int x = -dinoGrid; x <= dinoGrid; x++)
		for (int z = -dinoGrid; z <= dinoGrid; z++)
		{
			gls_Vec3f distVec = gls_vec3f_sub(_gls_camera.pos, gls_vec3f(75.f * x, 0.f, 75.f * z));
			float dist = gls_sqrt(gls_pow2(distVec.x) + gls_pow2(distVec.y) + gls_pow2(distVec.z));
			int lod = (int)(fminf(dist / 250.f, 5.f));

			if ((offset + x + z * (dinoGrid * 2 + 1)) % (lod + 1) == 0)
			{
				gls_pushState();
				gls_origin(75.f * x, 0.f, 75.f * z);
				gls_scale(0.1f, 0.1f, 0.1f);
				//gls_rotate(0.f, (float)game->ticks, 0.f);
				//gls_colorHSV(((float)game->ticks + (x + z) * 60.f) / 360.f, 1.f, 1.f);
				//gls_colorHSV(lod / 5.f * 0.7f, 1.f, 0.5f);
				game_drawModel(&game->paraVerts);
				gls_popState();
			}
			else
			{
				_gls_verts.length += game->paraVerts.length * 2;
			}
		}
	offset++;

	game_setTitle(game, "FPS: %u | Tri: %llu | Dinos: %d", 
		game->fps, _gls_verts.length / 6, 
		(dinoGrid * 2 + 1) * (dinoGrid * 2 + 1));
}

void game_playerInput(Game* game)
{
	// pause state
	bool escape = glfwGetKey(game->window, GLFW_KEY_ESCAPE);
	if (escape && !game->escLast)
	{
		game->pauseState = !game->pauseState;
		if (game->pauseState) // release cursor
		{
			glfwSetInputMode(game->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPos(game->window, game->screenW / 2.f, game->screenH / 2.f);
		}
		else // trap cursor, reset time
		{
			glfwSetInputMode(game->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPos(game->window, game->screenW / 2.f, game->screenH / 2.f);
			game->deltaTime = 0;
			game->lastTime = glfwGetTime();
		}
	}
	game->escLast = escape;
	if (game->pauseState)
		return;


	// movement
	int zDir = glfwGetKey(game->window, GLFW_KEY_S) - glfwGetKey(game->window, GLFW_KEY_W);
	int xDir = glfwGetKey(game->window, GLFW_KEY_D) - glfwGetKey(game->window, GLFW_KEY_A);
	game->player.acc.z = (cosf(gls_toRad(game->player.rot.y)) * zDir - 
		sinf(gls_toRad(game->player.rot.y)) * xDir) * game->player.moveSpeed;
	game->player.acc.x = (sinf(gls_toRad(game->player.rot.y)) * zDir +
		cosf(gls_toRad(game->player.rot.y)) * xDir) * game->player.moveSpeed;
	game->player.acc.y = (glfwGetKey(game->window, GLFW_KEY_SPACE) -
		glfwGetKey(game->window, GLFW_KEY_LEFT_SHIFT)) * game->player.moveSpeed;


	// look
	double mouseX, mouseY;
	glfwGetCursorPos(game->window, &mouseX, &mouseY);
	game->player.rot.y -= (float)(mouseX - game->screenW / 2.f) * game->lookSpeed;
	game->player.rot.x += (float)(game->screenH / 2.f - mouseY) * game->lookSpeed;
	glfwSetCursorPos(game->window, game->screenW / 2.f, game->screenH / 2.f);

	if (game->player.rot.x > 90.f)
		game->player.rot.x = 90.f;
	if (game->player.rot.x < -90.f)
		game->player.rot.x = -90.f;
	game->player.rot.y = gls_wrapDeg(game->player.rot.y);
	game->player.rot.z = gls_wrapDeg(game->player.rot.z);
}

void game_draw(Game* game)
{
	gls_begin(game->player.pos.x, game->player.pos.y, game->player.pos.z, 
		game->player.rot.x, game->player.rot.y, game->player.rot.z);

	_gls_verts.length += game->paraVerts.length * 2 * ((4 * 2 + 1) * (4 * 2 + 1) + 1);

	gls_draw(true);
	glfwSwapBuffers(game->window);

	double time = glfwGetTime();
	game->deltaFrameTime += time - game->lastFrameTime;
	game->lastFrameTime = time;

	if (game->deltaFrameTime > 1.0)
	{
		game->deltaFrameTime = 0.f;
		game->fps = game->fpsCount;
		game->fpsCount = 0;
	}

	game->fpsCount++;
}

void game_drawModel(gls_Stack* verts)
{
	for (size_t i = 0; i < verts->length; i += 3)
	{
		gls_Vec3f* vertPtr = stack_index(verts, i);
		gls_vertex(vertPtr[0].x, vertPtr[0].y, vertPtr[0].z);
		gls_vertex(vertPtr[1].x, vertPtr[1].y, vertPtr[1].z);
		gls_vertex(vertPtr[2].x, vertPtr[2].y, vertPtr[2].z);
		gls_applyLighting(stack_index(&_gls_verts, _gls_verts.length - 6));
	}
}

void game_setTitle(Game* game, char* fmt, ...)
{
	char titleBuf[100];

	va_list args;
	va_start(args, fmt);
	vsnprintf(titleBuf, 100, fmt, args);
	va_end(args);

	glfwSetWindowTitle(game->window, titleBuf);
}
