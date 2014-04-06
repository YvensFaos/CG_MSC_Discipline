#include "GLFW\glfw3.h"

#include "Vector3.h"
#include "Polygon2d.h"

#include <stdio.h>
#include <stdlib.h>

GLFWwindow* window;
Vector3* p;
Vector3* q;

Vector3* cP;
Vector3* cQ;

Polygon2D* clipWindow;
Polygon2D bound;

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
bool showBoundingBox;

void defineClipWindow(void)
{
	int length = 5;
	Edge2d* edges = new Edge2d[length];

	edges[0] = new Edge2d(new Vector3(0.15f, 0.55f), 
						  new Vector3(0.55f, 0.70f));
	edges[1] = new Edge2d(new Vector3(0.55f, 0.70f), 
						  new Vector3(0.75f, 0.70f));
	edges[2] = new Edge2d(new Vector3(0.75f, 0.70f), 
						  new Vector3(0.75f, 0.30f));
	edges[3] = new Edge2d(new Vector3(0.75f, 0.30f), 
						  new Vector3(0.35f, 0.20f));
	edges[4] = new Edge2d(new Vector3(0.35f, 0.20f), 
						  new Vector3(0.15f, 0.55f));

	clipWindow = new Polygon2D(length, edges);

	showBoundingBox = false;
	bound = clipWindow->getBoundBox();
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if(action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		if (key == GLFW_KEY_A) {
			showBoundingBox = !showBoundingBox;
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
	
	if(showBoundingBox)
	{
		

		glBegin(GL_LINES);
		int length = bound.length;
		for (int i = 0; i < length; i++)
		{
			glColor3f(1.f, .0f, .0f);
			glVertex3f(bound.edges[i].o.x, bound.edges[i].o.y, 0.f);
			glVertex3f(bound.edges[i].p.x, bound.edges[i].p.y, 0.f);
		}
		glEnd();
	}

	//Desenhar a área de desenho
	glBegin(GL_LINES);
	int length = clipWindow->length;
	for (int i = 0; i < length; i++)
	{
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(clipWindow->edges[i].o.x, clipWindow->edges[i].o.y, 0.f);
		glVertex3f(clipWindow->edges[i].p.x, clipWindow->edges[i].p.y, 0.f);
	}
	glEnd();

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
	defineClipWindow();

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