#include "player.h"

#include <stdio.h>
#include <time.h>
#include <GL\glut.h>

Player::Player(void)
{ 
	elapsedTime = 0.0f;
}

Player::~Player(void)
{ }

float Player::getTime(void)
{
	return 0.0f;
}

void Player::callBack()
{
	float ratio = 640 / 480.0f;
	gluPerspective(camera->pFOV, ratio, camera->pNear, camera->pFar);

	float timeNow = 0;
	float timeAfter = 0;

	timeNow = getTime();
		
	glMatrixMode(GL_MODELVIEW);

	glClearColor(.0f, .0f, .0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera->callUpdate(elapsedTime, camera);
	camera->cameraLookAt();
	if(elapsedTime != -1)
	{
		scenario->update(elapsedTime);
	}
	scenario->draw();

	timeAfter = getTime();
	if(elapsedTime != -1)
	{
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
		if(key == GLFW_KEY_UP)
		{
			camera->move(FORWARD);
		}
		if(key == GLFW_KEY_DOWN)
		{
			camera->move(BACKWARD);
		}
		if(key == GLFW_KEY_LEFT)
		{
			camera->move(LEFT);
		}
		if(key == GLFW_KEY_RIGHT)
		{
			camera->move(RIGHT);
		}
		if(key == GLFW_KEY_Z)
		{
			camera->move(RUP);
		}
		if(key == GLFW_KEY_X)
		{
			camera->move(RDOWN);
		}
		if(key == GLFW_KEY_C)
		{
			camera->move(UP);
		}
		if(key == GLFW_KEY_V)
		{
			camera->move(DOWN);
		}
		if(key == GLFW_KEY_B)
		{
			camera->move(RLEFT);
		}
		if(key == GLFW_KEY_N)
		{
			camera->move(RRIGHT);
		}
		if(key == GLFW_KEY_1)
		{
			initializeLights();
		}
		if(key == GLFW_KEY_2)
		{
			camera->zoomIn();
		}
		if(key == GLFW_KEY_3)
		{
			camera->zoomOut();
		}
		if(key == GLFW_KEY_4)
		{
			//DOLLY
			/*
			camera->zoomIn();
			camera->move(BACKWARD);
			*/

			camera->zoomOut();
			camera->move(FORWARD);
		}
		if(key == GLFW_KEY_5)
		{
			camera->print();
		}
		if(key == GLFW_KEY_Q)
		{
			float x = camera->position->x;
			float z = camera->position->z;

			camera->position->x = x*cos(10*pi180) - z*sin(10*pi180);
			camera->position->z = x*sin(10*pi180) + z*cos(10*pi180);
		}
		if(key == GLFW_KEY_W)
		{
			float x = camera->position->x;
			float z = camera->position->z;

			camera->position->x = x*cos(-10*pi180) - z*sin(-10*pi180);
			camera->position->z = x*sin(-10*pi180) + z*cos(-10*pi180);
		}
		if(key == GLFW_KEY_E)
		{
			if(elapsedTime > 0)
			{
				elapsedTime = -1;
			}
			else
			{
				elapsedTime = 0;
			}
		}
	}
}

void Player::initializeLights(void)
{
	GLfloat lightAmbient[] = {1.f, 1.f, 1.f, 1.f} ;
	GLfloat lightDiffuse[] = {1.f, 1.f, 1.f, 1.f} ;

	float basePos = 20.0f;
	float baseDir = 0.5f;

	GLfloat lightPos1[] = { basePos, basePos, basePos, 1.0 };
	GLfloat lightPos2[] = { -basePos, basePos, basePos, 1.0 };
	GLfloat lightPos3[] = { basePos, basePos, -basePos, 1.0 };
	GLfloat lightPos4[] = { -basePos, basePos, -basePos, 1.0 };

	GLfloat spotDir1[] =  { -baseDir, -baseDir, -baseDir };
	GLfloat spotDir2[] =  {  baseDir, -baseDir, -baseDir };
	GLfloat spotDir3[] =  { -baseDir, -baseDir,  baseDir };
	GLfloat spotDir4[] =  {  baseDir, -baseDir,  baseDir };

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

	float expoent = 30.0f;
	float spotCutoff = 40.0f;

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, expoent);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir2);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, expoent);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir3);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, expoent);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos4);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir4);	
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, expoent);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void Player::error(int e, const char* description)
{ 
	printf("%d:%s\n", e, description);
}

void Player::setUpScenario(Scene* scene)
{
	this->setUpScenario(scene->camera, scene->scenario);
}

void Player::setUpScenario(EDCamera* camera, Scenario* scenario)
{
	this->camera = camera;
	this->scenario = scenario;
}