#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GLFW\glfw3.h"
#include "scenario.h"
#include "edcamera.h"
#include "scene.h"

class Player
{
private:
	Scenario* scenario;
	EDCamera* camera;

	float elapsedTime;
public:
	Player(void);
	~Player(void);

	void initializeLights(void);
	void setUpScenario(Scene* scene);
	void setUpScenario(EDCamera* camera, Scenario* scenario);

	void callBack();
	bool running();
	void error(int e, const char* description);
	void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

	float getTime(void);
};

#endif
