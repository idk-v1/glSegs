#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include <GLFW/util/darkTheme.h>
#include <GLFW/util/sleep.h>

#include "glState/glState.h"

void drawRect(float xs, float ys, float zs)
{
	gls_Vec3f color = gls_getState()->color;
	
	// left
	gls_colorRGB(color.x - 0.1f, color.y, color.z);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);

	// right
	gls_colorRGB(color.x + 0.1f, color.y, color.z);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);

	// front
	gls_colorRGB(color.x, color.y, color.z + 0.1f);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);

		// back
	gls_colorRGB(color.x, color.y, color.z - 0.1f);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);

	// bottom
	gls_colorRGB(color.x, color.y - 0.1f, color.z);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, +0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, -0.5f * zs);
	gls_vertex(-0.5f * xs, -0.5f * ys, +0.5f * zs);

	// top
	gls_colorRGB(color.x, color.y + 0.1f, color.z);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, -0.5f * zs);
	gls_vertex(+0.5f * xs, +0.5f * ys, +0.5f * zs);
	gls_vertex(-0.5f * xs, +0.5f * ys, +0.5f * zs);

	gls_colorRGB(color.x, color.y, color.z);
}


void drawDino(float timer)
{
	gls_pushState(); // body
	gls_colorRGB(0.15f, 0.24f, 0.03f);
	drawRect(5.f, 17.f, 25.f);

		gls_pushState(); // body front
		gls_colorRGB(0.15f, 0.24f, 0.03f);
		gls_origin(0.f, 0.f, (25.f + 5.f) / 2.f);
		drawRect(5.f, 10.f, 5.f);

			gls_pushState(); // neck
			gls_colorRGB(0.15f, 0.24f, 0.03f);
			gls_origin(0.f, -1.f, 0.f);
			gls_translate(0.f, 0.f, 15.f / 2.f);
			gls_rotate(30.f + sinf(timer / 20.f) * 10.f, sinf(timer / 30.f) * 10.f, 0.f);
			drawRect(5.f, 8.f, 15.f);

				gls_pushState(); // neck upper
				gls_colorRGB(0.15f, 0.24f, 0.03f);
				gls_origin(0.f, 0.f, 15.f / 4.f);
				gls_translate(0.f, 0.f, 13.f / 2.f);
				gls_rotate(30.f + sinf(timer / 20.f) * 10.f, 0.f, 0.f);
				drawRect(5.f, 8.f, 13.f);

					gls_pushState(); // head
					gls_colorRGB(0.15f, 0.24f, 0.03f);
					gls_translate(0.f, -7.f / 2.f, 0.f);
					gls_origin(0.f, 0.f, (13.f + 13.f) / 2.f);
					gls_rotate(-90.f + sinf(timer / 20.f) * 10.f, 0.f, 0.f);
					drawRect(5.f, 7.f, 13.f);

						gls_pushState(); // upper jaw
						gls_colorRGB(0.15f, 0.24f, 0.03f);
						gls_origin(0.f, 1.5f, (13.f + 5.f) / 2.f);
						drawRect(5.f, 3.f, 5.f);
						gls_popState(); // upper jaw

						gls_pushState(); // lower jaw
						gls_colorRGB(0.15f, 0.24f, 0.03f);
						gls_origin(0.f, -1.5f, 13.f / 2.f);
						gls_translate(0.f, 0.f, 5.f / 2.f);
						gls_rotate(sinf(timer / 10.f) * 10.f, 0.f, 0.f);
						drawRect(5.f, 2.f, 5.f);
						gls_popState(); // lower jaw

						gls_pushState(); // crest start
						gls_colorRGB(0.15f, 0.24f, 0.03f);
						gls_origin(0.f, -2.f, -(13.f + 5.f) / 2.f + 4.5f);
						gls_rotate(60.f, 0.f, 0.f);
						drawRect(5.f, 10.f, 6.f);

							gls_pushState(); // crest
							gls_colorRGB(0.15f, 0.24f, 0.03f);
							gls_origin(0.f, 6.f / 2.f, 6.f / 2.f);
							gls_translate(0.f, 0.f, -10.f / 2.f);
							gls_rotate(-30.f, 0.f, 0.f);
							drawRect(5.f, 3.f, 10.f);

								gls_pushState(); // crest tip
								gls_colorRGB(0.15f, 0.24f, 0.03f);
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

		gls_pushState(); // body back
		gls_colorRGB(0.15f, 0.24f, 0.03f);
		gls_origin(0.f, 0.f, -(25.f + 6.f) / 2.f);
		gls_rotate(sinf(timer / 30.f) * 10.f, sinf(timer / 20.f) * 10.f, 0.f);
		drawRect(5.f, 12.f, 6.f);

			gls_pushState(); // body back back
			gls_colorRGB(0.15f, 0.24f, 0.03f);
			gls_origin(0.f, 0.f, -(6.f + 7.f) / 2.f);
			gls_rotate(0.f, sinf(timer / 20.f) * 10.f, 0.f);
			drawRect(5.f, 9.f, 7.f);

				gls_pushState(); // tail start
				gls_colorRGB(0.15f, 0.24f, 0.03f);
				gls_origin(0.f, 0.f, -(7.f + 5.f) / 2.f);
				gls_rotate(0.f, sinf(timer / 20.f) * 10.f, 0.f);
				drawRect(5.f, 6.f, 5.f);

					gls_pushState(); // tail
					gls_colorRGB(0.15f, 0.24f, 0.03f);
					gls_origin(0.f, 0.f, -(5.f + 12.f) / 2.f);
					gls_rotate(0.f, sinf(timer / 20.f) * 10.f, 0.f);
					drawRect(5.f, 3.f, 12.f);

						gls_pushState(); // tail tip
						gls_colorRGB(0.15f, 0.24f, 0.03f);
						gls_origin(0.f, 0.f, -(12.f + 12.f) / 2.f);
						gls_rotate(0.f, sinf(timer / 20.f) * 10.f, 0.f);
						drawRect(5.f, 2.f, 12.f);

						gls_popState(); // tail tip

					gls_popState(); // tail

				gls_popState(); // tail start

			gls_popState(); // body back back

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

	gls_Vec3f pos = { 0 };
	gls_Vec3f vel = { 0 };
	gls_Vec3f rot = { 0 };
	float lookSpeed = 0.25f;
	float moveSpeed = 0.75f;

	double lastTime = glfwGetTime();
	double deltaTime = 0;
	double timer = 0;

	bool pauseState = false;
	bool escStateLast = false;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, width / 2.f, height / 2.f);

	while (!glfwWindowShouldClose(window))
	{
		double time = glfwGetTime();
		deltaTime += time - lastTime;
		lastTime = time;

		glfwGetFramebufferSize(window, &width, &height);
		gls_setViewport(width, height);

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

		gls_Vec3f accel = { 0 };
		// movement
		int zDir = glfwGetKey(window, GLFW_KEY_W) - glfwGetKey(window, GLFW_KEY_S);
		if (zDir)
		{
			accel.z += cosf(gls_toRad(rot.y)) * zDir * moveSpeed;
			accel.x += sinf(gls_toRad(rot.y)) * zDir * moveSpeed;
		}
		int xDir = glfwGetKey(window, GLFW_KEY_D) - glfwGetKey(window, GLFW_KEY_A);
		if (xDir)
		{
			accel.z -= sinf(gls_toRad(rot.y)) * xDir * moveSpeed;
			accel.x += cosf(gls_toRad(rot.y)) * xDir * moveSpeed;
		}
		accel.y += (glfwGetKey(window, GLFW_KEY_SPACE) - 
			glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) * moveSpeed;

		if (!pauseState)
		{
			while (deltaTime >= 1.f / 60.f)
			{
				timer++;

				deltaTime -= 1.f / 60.f;

				gls_vec3f_add(&vel, accel);
				gls_vec3f_mul(&vel, gls_vec3f(0.8f, 0.8f, 0.8f));
				gls_vec3f_add(&pos, vel);

				if (glfwGetKey(window, GLFW_KEY_LEFT_ALT))
					gls_setWireframe(true);
				else
					gls_setWireframe(false);
			}

			double mouseX, mouseY;
			glfwGetCursorPos(window, &mouseX, &mouseY);
			rot.y += (float)(mouseX - width / 2.f) * lookSpeed;
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

			drawDino((float)timer);

			gls_draw(true);
			glfwSwapBuffers(window);
		}

		glfwPollEvents();

		glfwSleep(1.f / 1000.f);
	}
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}