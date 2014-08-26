#include <stdio.h>

#include "GLFWWrapper.h"
#include "player.h"

#include "cannonsScene.h"
#include "transformScene.h"
#include "kickingScene.h"
#include "cameraScene.h"
#include "loadObjScene.h"

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
	player->setUpScenario(new LoadObjScene());

	GLFWWrapper::initialize(callBack);
	player->initializeLights();
	GLFWWrapper::running_callback(running);
	GLFWWrapper::keyboard_callback(keyboard);

	GLFWWrapper::glLoop();
	return 0;
}