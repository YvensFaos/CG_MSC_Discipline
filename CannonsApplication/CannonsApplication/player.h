#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GLFW\glfw3.h"
#include "scenario.h"

class Player
{
private:
	Scenario* scenario;

public:
	Player(void);
	~Player(void);

	void setUpScenario(void);

	void callBack();
	bool running();
	void error(int e, const char* description);
	void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

	float getTime(void);
};

#endif
