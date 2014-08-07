#include "glfwWrapper.h"

#include <stdio.h>
#include <GL\glut.h>

float GLFWWrapper::ratio;
GLFWwindow* GLFWWrapper::window;
errorCallback GLFWWrapper::error;
loopCallback GLFWWrapper::callback;
runningCallback GLFWWrapper::running;
keyboadCallback GLFWWrapper::keyboard;

void GLFWWrapper::initialize(loopCallback callback)
{
	glfwSetErrorCallback(GLFWWrapper::error_callback);
	glfwInit();

	int width = 640;
	int height = 480;
	char* title = "Cannons Application";
	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window)
    {
		glfwTerminate();
    }

	glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, GLFWWrapper::key_callback);

	ratio = width / (float) height;

	loop_callback(callback);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glShadeModel(GL_SMOOTH);
}

void GLFWWrapper::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{ keyboard(window, key, scancode, action, mods); }

void GLFWWrapper::error_callback(int e, const char* description)
{ error(e, description); }

void GLFWWrapper::loop_callback(loopCallback callback)
{ GLFWWrapper::callback = callback; }

void GLFWWrapper::running_callback(runningCallback callback)
{ GLFWWrapper::running = callback; }

void GLFWWrapper::keyboard_callback(keyboadCallback callback)
{ GLFWWrapper::keyboard = callback; }

void GLFWWrapper::error_callback(errorCallback callback)
{ GLFWWrapper::error = callback; }

void GLFWWrapper::glLoop()
{
	while (!glfwWindowShouldClose(window) && (running)())
    {
		glViewport(0, 0, 640, 480);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

		(callback)();

		glFlush();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glfwDestroyWindow(window);
}