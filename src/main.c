#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "game/game.h"

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
	gls_colorHSV(0.20f, 0.65f, 0.18f);
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
		gls_origin(0.f, 0.f, -25.f/ 2.f);
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


int main(int argc, char** argv)
{
	Game game = game_init(800, 600, "");

	while (game.isOpen)
	{
		game_update(&game);
		game_setTitle(&game, 
			"Pos(x, y, z): %1.f, %1.f, %1.f | Rot(x, y, z): %1.f, %1.f, %1.f",
			game.player.pos.x, game.player.pos.y, game.player.pos.z, 
			game.player.rot.x, game.player.rot.y, game.player.rot.z);
		game_draw(&game);
	}

	game_delete(&game);

	return 0;
}