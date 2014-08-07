#include <stdio.h>

#include "GLFWWrapper.h"
#include "player.h"

Player* player;

void callBack()
{
	player->callBack();
}

bool running()
{
	return player->running();
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	player->keyboard(window, key, scancode, action, mods);
}

int main()
{
	player = new Player();

	GLFWWrapper::initialize(callBack);
	GLFWWrapper::running_callback(running);
	GLFWWrapper::keyboard_callback(keyboard);

	GLFWWrapper::glLoop();
	return 0;
}