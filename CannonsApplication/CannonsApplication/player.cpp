#include "player.h"

#include <stdio.h>

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::callBack()
{
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