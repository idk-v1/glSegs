#include "game.h"

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

	gls_setViewport(game.screenW, game.screenH);

	gls_init();
	game.fov = 90.f;
	game.lookSpeed = 0.25f;
	gls_setFOV(game.fov);
	gls_setNearFar(0.1f, 10000.f);

	//gls_addGlobalLight(45.f, 0.f, 0.f, gls_colorHSVtoRGB(0.f, 0.f, 1.f));
	gls_addPointLight(0.f, 50.f, 0.f, 500.f, gls_colorHSVtoRGB(0.f, 0.f, 1.f));

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

	game_setTitle(game, "FPS: %u | Tri: %llu", game->fps, _gls_verts.length / 6);

	glfwPollEvents();

	game->isOpen = !glfwWindowShouldClose(game->window);
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

	int dinoGrid = 3;
	for (int x = -dinoGrid; x <= dinoGrid; x++)
		for (int z = -dinoGrid; z <= dinoGrid; z++)
		{
			gls_pushState();
			gls_origin(75.f * x, 0.f, 75.f * z);
			gls_scale(0.1f, 0.1f, 0.1f);
			gls_rotate(0.f, (float)game->ticks, 0.f);
			gls_colorHSV(((float)game->ticks + (x + z) * 60.f) / 360.f, 0.5f, 1.f);
			game_drawModel(&game->paraVerts);
			gls_popState();
		}

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
	for (size_t i = 0; i < verts->length; i++)
	{
		gls_Vec3f* vertPtr = stack_index(verts, i);
		gls_vertex(vertPtr->x, vertPtr->y, vertPtr->z);
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
