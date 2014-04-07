#include "GLFW\glfw3.h"

#include "Vector3.h"
#include "Polygon2d.h"

#include <stdio.h>
#include <stdlib.h>

//UP DOWN LEFT RIGHT
int U = 0x08;
int D = 0x04;
int L = 0x02;
int R = 0x01;

GLFWwindow* window;
Vector3* p;
Vector3* q;

Vector3 cP;
Vector3 cQ;

Polygon2D* clipWindow;
Polygon2D bound;

float _width = 640;
float _height = 480;

bool setP;
bool setQ;
bool setPoints;
bool clippedLine;
bool showBoundingBox;

float max(float a, float b)
{
	return (a > b)? a : b;
}

float min(float a, float b)
{
	return (a < b)? a : b;
}

int classifyRegions(Vector3 v)
{
	int vMask = 0;

	if(v.y > clipWindow->majorDiagonal.y)
	{
		vMask |= U;
	}else if(v.y < clipWindow->minorDiagonal.y)
	{
		vMask |= D;
	}

	if(v.x < clipWindow->minorDiagonal.x)
	{
		vMask |= L;
	}else if(v.x > clipWindow->majorDiagonal.x)
	{
		vMask |= R;
	}

	return vMask;
}

bool cyrusBeck(void)
{
	bool visible = true;

	int pMask = classifyRegions(p);
	int qMask = classifyRegions(q);

	if(pMask & qMask)
	{
		printf("Trivial Reject\n");
		return false;	
	}

	Vector3 direction = q->subtract(p);
	Vector3 w, normal;
	Edge2d edge;
	Edge2d parametricLine = Edge2d(p, q);

	float dotW, dotD;
	float t;
	float t0 = 0;
	float t1 = 1;
	int length = clipWindow->length;

	for(int i = 0; i < length; i++)
	{
		edge = clipWindow->edges[i];
		w = p->subtract(edge.o);
		normal = clipWindow->normals[i];

		dotD = direction.dotProduct(normal);
		dotW = w.dotProduct(normal);

		if(dotD != 0)
		{
			t = -(dotW/dotD);
			if(dotD > 0)
			{
				if(t > 1)
				{
					visible = false;
				}
				else
				{
					t0 = max(t, t0);
				}
			}
			else
			{
				if(t < 0)
				{
					visible = false;
				}
				else
				{
					t1 = min(t, t1);
				}
			}
		}
	}

	printf("T0 = %f e T1 = %f\n",t0, t1);

	cP = parametricLine.parametric(t0);
	cQ = parametricLine.parametric(t1);

	return visible;
}

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
						  new Vector3(0.35f, 0.25f));
	edges[4] = new Edge2d(new Vector3(0.35f, 0.25f),
						  new Vector3(0.15f, 0.55f));

	clipWindow = new Polygon2D(length, edges);

	showBoundingBox = false;
	bound = clipWindow->getBoundBox();
	clipWindow->calculateOuter();
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

		if (key == GLFW_KEY_S) {
			clipWindow->printConsole();
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
			bool visible = cyrusBeck();
			if(!visible)
			{
				printf("Invisible\n");
				cP = Vector3();
				cQ = Vector3();
			}
			
			clippedLine = true;
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
		//Desenha bounding box
		glBegin(GL_LINES);
		int length = bound.length;
		for (int i = 0; i < length; i++)
		{
			glColor3f(1.f, .0f, .0f);
			glVertex3f(bound.edges[i].o.x, bound.edges[i].o.y, 0.f);
			glVertex3f(bound.edges[i].p.x, bound.edges[i].p.y, 0.f);
		}
		glEnd();

		//Desenha centro
		glBegin(GL_LINES);
		Vector3 center = clipWindow->center;
		glColor3f(1.f, .0f, .0f);

		glVertex3f(center.x, center.y, 0);
		glVertex3f(center.x + 0.01f, center.y, 0);

		glVertex3f(center.x, center.y, 0);
		glVertex3f(center.x - 0.01f, center.y, 0);

		glVertex3f(center.x, center.y, 0);
		glVertex3f(center.x, center.y + 0.01f, 0);

		glVertex3f(center.x, center.y, 0);
		glVertex3f(center.x, center.y - 0.01f, 0);
		glEnd();

		//Desenha normais
		glBegin(GL_LINES);
		length = clipWindow->length;
		for (int i = 0; i < length; i++)
		{
			glColor3f(0.f, 1.0f, .0f);
			Vector3 midPoints = clipWindow->edges[i].parametric(0.5f);
			Vector3 normal = clipWindow->normals[i];

			glVertex3f(midPoints.x, midPoints.y, 0.f);
			glVertex3f(midPoints.x + normal.x, midPoints.y + normal.y, 0.f);
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
		glVertex3f(cP.x, cP.y, 0.f);
		glVertex3f(cQ.x, cQ.y, 0.f);
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