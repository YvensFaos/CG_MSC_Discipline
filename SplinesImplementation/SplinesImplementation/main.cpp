#include "GLFW\glfw3.h"
#include "Vector3.h"
#include "CubicHermite.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

GLFWwindow* window;
CubicHermite* spline;

GLfloat  _width = 640;
GLfloat _height = 400;

#define pi 3.14159265359
#define max(a,b) (a > b)?a:b;
#define min(a,b) (a < b)?a:b;

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if(action == GLFW_PRESS || action == GLFW_REPEAT) {
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
		x /= 640.f;
		y /= 480.f;
		y -= 1;
		y *= -1;

		printf("Mouse = x[%f] e y[%f]\n",x,y);
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
	glOrtho(-2.f, 2.f, -2.f, 2.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Desenhar a �rea de desenho
	glBegin(GL_LINES);
	//Desenhar eixos
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-2.f, .0f, 0.f);
	glVertex3f( 2.f, .0f, 0.f);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(.0f, -2.f, 0.f);
	glVertex3f(.0f,  2.f, 0.f);
	glEnd();

	spline->drawSpline(50);

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

	window = glfwCreateWindow(_width, _height, "Splitting Polygons", NULL, NULL);
	Vector3 points[] = {Vector3(-1.8f,0.5f,0), Vector3(1.8f,0.f,0), Vector3(0.f,4.f,0), Vector3(-1.f,10.f,0)};
	spline = new CubicHermite();
	spline->setPoints(points, 4);

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