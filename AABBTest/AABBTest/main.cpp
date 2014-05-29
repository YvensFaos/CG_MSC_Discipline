#include "GLFW\glfw3.h"

#include "Vector3.h"
#include "Polygon2d.h"

#include <stdio.h>
#include <stdlib.h>

GLFWwindow* window;
float _width = 640;
float _height = 480;
bool collide = false;

Polygon2D* p1;
Polygon2D* p2;

void generateBoxes(void)
{
	Vector3 points[] = {Vector3(.1f,.1f,.0f), Vector3(.1f,.3f,.0f), Vector3(.3f,.3f,.0f), Vector3(.3f,.1f,.0f)};

	p1 = new Polygon2D(4, points);

	Vector3 points2[] = {Vector3(.6f,.2f,.0f), Vector3(.6f,.7f,.0f), Vector3(.9f,.7f,.0f), Vector3(.9f,.2f,.0f)};

	p2 = new Polygon2D(4, points2);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if(action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key == GLFW_KEY_A) {
		}

		if (key == GLFW_KEY_S) {
		}

		if (key == GLFW_KEY_UP) {
			p1->translate(0.f,.1f);
		}
		if (key == GLFW_KEY_DOWN) {
			p1->translate(0.f,-.1f);
		}
		if (key == GLFW_KEY_LEFT) {
			p1->translate(-.1f,.0f);
		}
		if (key == GLFW_KEY_RIGHT) {
			p1->translate(.1f,.0f);
		}
	}
}

void glfwMouseCallback(GLFWwindow* window, int button, int action, int mods) 
{
	if(action == GLFW_PRESS) {
		
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

	glBegin(GL_LINES);
	glColor3f(0.f,0.f,1.f);
	glVertex3f(0.f, .5f, 0.f); 
	glVertex3f(1.f, .5f, 0.f); 
	glEnd();

	collide = p2->collide(p1); // || p2->collide(p1);;
	if(!collide)
	{
		glColor3f(1.f,.0f,.0f);
	}
	else
	{
		glColor3f(.0f,1.f,.0f);
	}
	glBegin(GL_QUADS);
	for(int i = 0; i < p1->length; i++)
	{
		glVertex3f(p1->points[i].x, p1->points[i].y, p1->points[i].z);
	}
	glEnd();

	glBegin(GL_QUADS);
	for(int i = 0; i < p2->length; i++)
	{
		glVertex3f(p2->points[i].x, p2->points[i].y, p2->points[i].z);
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

	window = glfwCreateWindow(_width, _height, "AABB Test", NULL, NULL);

	if (!window)
    {
        glfwTerminate();
        return 0;
    }

	generateBoxes();

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