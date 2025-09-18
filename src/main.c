#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <GLFW/util/darkTheme.h>
#include <GLFW/util/sleep.h>

#include "glState/glState.h"

#include "objReader/objReader.h"

void drawRect(float xs, float ys, float zs)
{
	gls_Vec3f color = gls_colorRGBtoHSV(gls_getState()->color);
	
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
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int width = 800, height = 600;
	GLFWwindow* window = glfwCreateWindow(width, height, "", NULL, NULL);
	glfwSetWindowTheme(window, GLFW_THEME_AUTO);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	gls_setViewport(width, height);

	gls_init();
	gls_setNearFar(0.1f, 10000.f);
	gls_setFOV(90.f);

	gls_Stack lpParaVerts = obj_readVerts("para/lowpoly_parasaur.obj");

	gls_Vec3f pos = { 0 };
	gls_Vec3f vel = { 0 };
	gls_Vec3f rot = { 0 };
	float lookSpeed = 0.25f;
	float moveSpeed = 0.75f;

	double lastTime = glfwGetTime();
	double deltaTime = 0;
	double timer = 0;

	bool tabLast = false;
	bool wireframe = false;

	float fov = 90.f;

	bool pauseState = false;
	bool escStateLast = false;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, width / 2.f, height / 2.f);

	while (!glfwWindowShouldClose(window))
	{
		double time = glfwGetTime();
		deltaTime += time - lastTime;
		lastTime = time;

		int lastWidth = width;
		int lastHeight = height;
		glfwGetFramebufferSize(window, &width, &height);
		if (lastWidth != width || lastHeight != height)
			gls_setViewport(width, height);

		// pause state
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) && !escStateLast)
		{
			pauseState = !pauseState;
			if (pauseState)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				glfwSetCursorPos(window, width / 2.f, height / 2.f);
			}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetCursorPos(window, width / 2.f, height / 2.f);
				deltaTime = 0;
				lastTime = glfwGetTime();
			}
		}
		escStateLast = glfwGetKey(window, GLFW_KEY_ESCAPE);

		// movement
		gls_Vec3f accel = { 0 };
		int zDir = glfwGetKey(window, GLFW_KEY_S) - glfwGetKey(window, GLFW_KEY_W);
		int xDir = glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A);
		accel.z += (cosf(gls_toRad(rot.y)) * zDir - sinf(gls_toRad(rot.y)) * xDir) * moveSpeed;
		accel.x += (sinf(gls_toRad(rot.y)) * zDir + cosf(gls_toRad(rot.y)) * xDir) * moveSpeed;
		accel.y += (glfwGetKey(window, GLFW_KEY_SPACE) - 
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) * moveSpeed;

		bool tab = glfwGetKey(window, GLFW_KEY_TAB);
		if (tab && !tabLast)
		{
			wireframe = !wireframe;
			gls_setWireframe(wireframe);
		}
		tabLast = tab;

		if (!pauseState)
		{
			// update loop
			while (deltaTime >= 1.f / 60.f)
			{
				timer++;

				deltaTime -= 1.f / 60.f;

				gls_vec3f_add(&vel, accel);
				gls_vec3f_mul(&vel, gls_vec3f(0.8f, 0.8f, 0.8f));
				gls_vec3f_add(&pos, vel);

				if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT))
				{
					if (fov > 10.f)
						fov -= 1.f;
					if (fov < 10.f)
						fov = 10.f;
				}
				else
				{
					if (fov < 90.f)
						fov += 1.f;
					if (fov > 90.f)
						fov = 90.f;
				}
				gls_setFOV(fov);
			}

			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			rot.y -= (float)(mouseX - width / 2.f) * lookSpeed;
			rot.x += (float)(mouseY - height / 2.f) * lookSpeed;
			glfwSetCursorPos(window, width / 2.f, height / 2.f);

			rot.x = gls_wrapDeg(rot.x);
			rot.y = gls_wrapDeg(rot.y);
			rot.z = gls_wrapDeg(rot.z);


			char titleBuf[100];
			snprintf(titleBuf, 100,
				"Pos(x, y, z): %1.f, %1.f, %1.f | Rot(x, y, z): %1.f, %1.f, %1.f",
				pos.x, pos.y, pos.z, rot.x, rot.y, rot.z);
			glfwSetWindowTitle(window, titleBuf);


			gls_begin(pos.x, pos.y, pos.z, rot.x, rot.y, rot.z);

			gls_scale(0.1f, 0.1f, 0.1f);
			gls_rotate(0.f, (float)timer, 0.f);
			
			for (int x = -5; x <= 5; x++)
				for (int z = -5; z <= 5; z++)
				{
					gls_origin(50.f * x, 0.f, 50.f * z);
					for (size_t i = 0; i < lpParaVerts.length; i++)
					{
						gls_colorHSV((float)timer / 360.f + i * 0.1f, 1.f, 1.f);
						gls_vertex(((gls_Vec3f*)stack_index(&lpParaVerts, i))->x,
							((gls_Vec3f*)stack_index(&lpParaVerts, i))->y,
							((gls_Vec3f*)stack_index(&lpParaVerts, i))->z);
					}
				}

			gls_draw(true);
			glfwSwapBuffers(window);
		}

		glfwPollEvents();

		//glfwSleep(1.f / 1000.f);
	}
	glfwDestroyWindow(window);

	stack_free(&lpParaVerts);

	glfwTerminate();
	return 0;
}