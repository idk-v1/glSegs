#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "game/game.h"


int main(int argc, char** argv)
{
	Game game = game_init(800, 600, "");

	while (game.isOpen)
	{
		game_update(&game);
		game_draw(&game);
	}

	game_delete(&game);

	return 0;
}