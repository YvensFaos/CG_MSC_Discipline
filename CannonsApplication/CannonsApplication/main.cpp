#include <stdio.h>

#include "GLFWWrapper.h"
#include "player.h"

#include "cannonsScene.h"
#include "transformScene.h"
#include "kickingScene.h"
#include "cameraScene.h"
#include "loadObjScene.h"
#include "standLuxorScene.h"
#include "kickingLamp.h"
#include "articulatedLuxorScene.h"
#include "trinityScene.h"
#include "neoMatrixScene.h"
#include "pendulumScene.h"

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
	//player->setUpScenario(new CannonsScene());
	//player->setUpScenario(new TransformScene());
	//player->setUpScenario(new KickingScene());
	//player->setUpScenario(new CameraScene());
	//player->setUpScenario(new LoadObjScene());
	//player->setUpScenario(new StandLuxorScene());
	//player->setUpScenario(new KickingLamp());
	player->setUpScenario(new ArticulatedLuxorScene());
	//player->setUpScenario(new TrinityScene());
	//player->setUpScenario(new NeoMatrixScene());
	//player->setUpScenario(new PendulumScene());

	GLFWWrapper::initialize(callBack);
	player->initializeLights();
	GLFWWrapper::running_callback(running);
	GLFWWrapper::keyboard_callback(keyboard);

	GLFWWrapper::glLoop();
	return 0;
}