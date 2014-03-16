#include "GLFW\glfw3.h"
#include "Vector3.h"
#include <stdio.h>

//UP DOWN LEFT RIGHT
int U = 0x08;
int D = 0x04;
int L = 0x02;
int R = 0x01;

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

int classifyRegions(Vector3 v)
{
	int vMask = 0;

	if(v.y > _yMax)
	{
		vMask |= U;
	}else if(v.y < _yMin)
	{
		vMask |= D;
	}

	if(v.x < _xMin)
	{
		vMask |= R;
	}else if(v.x > _xMax)
	{
		vMask |= L;
	}

	return vMask;
}

void cohenSutherland(void)
{
	int pMask = classifyRegions(*p);
	int qMask = classifyRegions(*q);
	printf("%d %d \n", pMask, qMask);


}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if(action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if(key == GLFW_KEY_A)
		{
			if(setPoints)
			{
				printf("(P) %f %f %f", p->x, p->y, p->z);
				printf("(Q) %f %f %f", q->x, q->y, q->z);
			}
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
		printf("%f %f\n", x, y);
		if(!setP)
		{
			p = new Vector3(x, y, 0.f);
			setP = true;
			printf("setP\n");
		}
		else
		if(!setQ)
		{
			q = new Vector3(x, y, 0.f);
			setQ =  true;
			setPoints = true;
			printf("setQ\n");

			cohenSutherland();
		}
		else
		if(setPoints)
		{
			setP = setQ = setPoints = false;
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

	if(setPoints)
	{
		glBegin(GL_LINE_STRIP);
		glColor3f(0.f, 0.f, 1.f);
			glVertex3f(p->x, p->y, p->z);
			glVertex3f(q->x, q->y, q->z);
		glEnd();


	}

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

	window = glfwCreateWindow(_width, _height, "Cohen Sutherland", NULL, NULL);
	setPoints = false;
	setP = false;
	setQ = false;

	if (!window)
    {
        glfwTerminate();
        return 0;
    }

	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 800, 120);
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