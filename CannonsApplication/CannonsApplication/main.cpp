#include <stdio.h>

#include "GLFWWrapper.h"
#include "player.h"
#include "cannonsScene.h"

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
	player->initializeLights();
	player->setUpScenario(new CannonsScene());

	GLFWWrapper::initialize(callBack);
	GLFWWrapper::running_callback(running);
	GLFWWrapper::keyboard_callback(keyboard);

	GLFWWrapper::glLoop();
	return 0;
}