#include "GLFW\glfw3.h"
#include "Vector3.h"
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* window;
Vector3* p;
Vector3* q;

Vector3* cP;
Vector3* cQ;

float _width = 640;
float _height = 480;

float _xMin = 0.2f;
float _xMax = 0.8f;
float _yMin = 0.2f;
float _yMax = 0.8f;

bool setP;
bool setQ;
bool setPoints;
bool clippedLine;

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if(action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		
	}
}

void glfwMouseCallback(GLFWwindow* window, int button, int action, int mods) 
{
	if(action == GLFW_PRESS) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		//printf("%f %f\n", x, y);
		x /= 640.f;
		y /= 480.f;
		y -= 1;
		y *= -1;

		if(!setP)
		{
			printf("Set P: %f %f\n", x, y);
			p = new Vector3(x, y, 0.f);
			setP = true;
		}
		else
		if(!setQ)
		{
			printf("Set Q: %f %f\n", x, y);
			q = new Vector3(x, y, 0.f);
			setQ =  true;
			setPoints = true;
		}
		else
		if(!clippedLine)
		{
			printf("Bounds: %f %f %f %f\n", _xMin, _xMax, _yMin, _yMax);
			//cohenSutherland();
			//algoritmo do cyrus beck
		}
		else
		if(setPoints)
		{
			setP = setQ = setPoints = clippedLine = false;
			system("cls");
			printf("Clear\n");
		}
	}
}

void display(void)
{
	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);

	ratio = width / (float) height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.f, 1.f, 0.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Desenhar a área de desenho
	/*
	glBegin(GL_QUADS);
		glColor4f(0.05f, 0.05f, 0.05f, .5f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f,  1.f, 0.f);
		glVertex3f( 1.f,  1.f, 0.f);
		glVertex3f( 1.f, 0.f, 0.f);
	glEnd();

	glBegin(GL_QUADS);
		glColor4f(0.3f, 0.3f, 0.3f, .5f);
		glVertex3f(_xMin, _yMin, 0.f);
		glVertex3f(_xMin, _yMax, 0.f);
		glVertex3f(_xMax, _yMax, 0.f);
		glVertex3f(_xMax, _yMin, 0.f);
	glEnd();
	*/

	glBegin(GL_LINES);
	if(setPoints)
	{
		glColor3f(.0f, .0f, 1.f);
		glVertex3f(p->x, p->y, 0.f);
		glVertex3f(q->x, q->y, 0.f);
	}
	if(clippedLine)
	{
		glColor3f(1.f, 1.f, 0.f);
		glVertex3f(cP->x, cP->y, 0.f);
		glVertex3f(cQ->x, cQ->y, 0.f);
	}
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

int main(void)
{
	if (!glfwInit())
	{
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	window = glfwCreateWindow(_width, _height, "Cyrus Beck", NULL, NULL);
	setPoints = false;
	setP = false;
	setQ = false;
	clippedLine = false;

	if (!window)
    {
        glfwTerminate();
        return 0;
    }

	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 620, 120);
	glfwSetKeyCallback(window, glfwKeyCallback);
	glfwSetMouseButtonCallback(window, glfwMouseCallback);

	if(window != 0)
	{
		while (!glfwWindowShouldClose(window))
		{
			display();
		}
		glfwTerminate();
	}
    return 0;
}