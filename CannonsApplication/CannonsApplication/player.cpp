#include "player.h"

#include <stdio.h>
#include <time.h>

Player::Player(void)
{
}

Player::~Player(void)
{
}

float Player::getTime(void)
{
	return 0.0f;
}

void Player::callBack()
{
	float timeNow = 0;
	float timeAfter = 0;
	float elapsedTime = 0;
	while(running())
	{
		timeNow = getTime();

		timeAfter = getTime();
		elapsedTime = timeAfter - timeNow;
		if(elapsedTime <= 0.016f)
		{
			elapsedTime = 0.016f;
		}
	}
}

bool Player::running()
{
	return true;
}

void Player::keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void Player::error(int e, const char* description)
{ 
	printf("%d:%s\n", e, description);
}

void Player::setUpScenario(void)
{

}