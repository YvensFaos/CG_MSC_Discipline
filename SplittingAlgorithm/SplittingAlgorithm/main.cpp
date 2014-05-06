#include "GLFW\glfw3.h"

#include "Vector3.h"
#include "Polygon2d.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

GLFWwindow* window;

int qtt;
bool splitLine;
Vector3* p;
Vector3* q;
Polygon2D* polygons;
Polygon2D* points;
Polygon2D* points2;

float _width = 640;
float _height = 480;

#define pi 3.14159265359
#define max(a,b) (a > b)?a:b;
#define min(a,b) (a < b)?a:b;

int polygonType = 0;

void defineClipWindow(void)
{
#pragma region initialPolygon
	switch (polygonType)
	{
	case 0:
		{
			int length = 6;
			Edge2d* edges = new Edge2d[length];

			int i = 0;
			edges[i++] = new Edge2d(new Vector3(0.15f, 0.25f), 
								  new Vector3(0.85f, 0.25f));

			edges[i++] = new Edge2d(new Vector3(0.85f, 0.25f), 
								  new Vector3(0.55f, 0.60f));

			edges[i++] = new Edge2d(new Vector3(0.55f, 0.60f), 
								  new Vector3(0.85f, 0.90f));

			edges[i++] = new Edge2d(new Vector3(0.85f, 0.90f), 
								  new Vector3(0.15f, 0.90f));

			edges[i++] = new Edge2d(new Vector3(0.15f, 0.90f), 
								  new Vector3(0.35f, 0.60f));

			edges[i++] = new Edge2d(new Vector3(0.35f, 0.60f),
								  new Vector3(0.15f, 0.25f));

			polygons = new Polygon2D[1];
			qtt = 1;
			polygons[0] = Polygon2D(length, edges);
		}
		break;
	case 1:
		{
			int length = 5;
			Edge2d* edges = new Edge2d[length];

			int i = 0;
			edges[i++] = new Edge2d(new Vector3(0.15f, 0.25f), 
								  new Vector3(0.85f, 0.25f));

			edges[i++] = new Edge2d(new Vector3(0.85f, 0.25f), 
								  new Vector3(0.65f, 0.60f));

			edges[i++] = new Edge2d(new Vector3(0.65f, 0.60f), 
								  new Vector3(0.85f, 0.90f));

			edges[i++] = new Edge2d(new Vector3(0.85f, 0.90f), 
								  new Vector3(0.15f, 0.90f));

			edges[i++] = new Edge2d(new Vector3(0.15f, 0.90f), 
								  new Vector3(0.15f, 0.25f));

			polygons = new Polygon2D[1];
			qtt = 1;
			polygons[0] = Polygon2D(length, edges);
		}
		break;
	case 2:
		{
			int length = 5;
			Edge2d* edges = new Edge2d[length];

			int i = 0;
			edges[i++] = new Edge2d(new Vector3(0.15f, 0.25f), 
								  new Vector3(0.85f, 0.25f));

			edges[i++] = new Edge2d(new Vector3(0.85f, 0.25f), 
								  new Vector3(0.45f, 0.60f));

			edges[i++] = new Edge2d(new Vector3(0.45f, 0.60f), 
								  new Vector3(0.85f, 0.90f));

			edges[i++] = new Edge2d(new Vector3(0.85f, 0.90f), 
								  new Vector3(0.15f, 0.90f));

			edges[i++] = new Edge2d(new Vector3(0.15f, 0.90f), 
								  new Vector3(0.15f, 0.25f));

			polygons = new Polygon2D[1];
			qtt = 1;
			polygons[0] = Polygon2D(length, edges);
		}
		break;
	}
#pragma endregion
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
#pragma region movimentos e controles
	float modifier = 1.f;
	if(mods == GLFW_MOD_SHIFT)
	{
		modifier = .1f;
	}
	if(action == GLFW_PRESS || action == GLFW_REPEAT) {
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if(key == GLFW_KEY_W)
		{
			if(splitLine)
			{
				points->printConsole();
			}
		}

		if (key == GLFW_KEY_UP) {
			polygons[0].translate(.0f, .05f*modifier);
		}

		if (key == GLFW_KEY_DOWN) {
			polygons[0].translate(.0f, -.05f*modifier);
		}

		if (key == GLFW_KEY_LEFT) {
			polygons[0].translate(-0.05f*modifier, .0f);
		}

		if (key == GLFW_KEY_RIGHT) {
			polygons[0].translate(0.05f*modifier, .0f);
		}
		if (key == GLFW_KEY_A) {
			polygons[0].rotate(5.f*modifier);
		}
		if (key == GLFW_KEY_S) {
			polygons[0].rotate(-5.f*modifier);
		}
#pragma endregion

		if(key == GLFW_KEY_D)
		{
			Polygon2D* pol = nullptr;
			int length = 0; 
			bool solved = false;
			int i = 0;

			for (int h = 0; h < qtt; h++)
			{
				pol =  &polygons[h];
				length = pol->length;
				solved = false;
				i = 0;
				//Resolve de polígono em polígono
				while(!solved)
				{
					Vector3* i1 = &pol->points[i];
					float x = i1->x;
					float y = i1->y;
					pol->translate(-x,-y);
	
					Vector3* i2 = &pol->points[(i+1)%length];

					float magnitude = i2->magnitude();
					float angle = (acos(i2->x/(float)magnitude))*180/pi;
					if(i2->y < 0)
					{
						angle *= -1;
					}
					pol->rotate(-angle);

					Vector3* i3 = &pol->points[(i+2)%length];
					if(i3->y < 0)
					{
						int j = (i+3)%length;
						int counter = 0;
						bool found = false;
						Vector3* i4 = nullptr;
						while(counter < length)
						{
							i4 = &pol->points[(j+counter)%length];
							if(i4->y >= 0)
							{
								found = true;
								break;
							}
							counter++;
						}

						if(found)
						{
#pragma region determinar size1
							int size1 = 0;
							int state = 0;
							Vector3* aux = nullptr;
							for (int k = 0; k < length; k++)
							{
								aux = &pol->points[k];
								switch (state)
								{
								case 0:
									{
										if(aux->equals(i2))
										{
											state++;
										}
										size1++;
									}
									break;
								case 1:
									{
										if(aux->equals(i4))
										{
											size1++;
											state++;
										}
									}
									break;
								case 2:
									{
										size1++;
									}
									break;
								}
							}
#pragma endregion

#pragma region determinar poligono 1
							state = 0;
							printf("size1 = %d\n", size1);
							Vector3* vec1 = new Vector3[size1];
							int kk = 0;
							for (int k = 0; k < length; k++)
							{
								aux = &pol->points[k];
							
								switch (state)
								{
								case 0:
									{
										vec1[kk++] = Vector3(aux);
										if(aux->equals(i2))
										{
											state++;
										}
									}
									break;
								case 1:
									{
										if(aux->equals(i4))
										{
											vec1[kk++] = Vector3(aux);
											state++;
										}
									}
									break;
								case 2:
									{
										vec1[kk++] = Vector3(aux);
									}
									break;
								}
							}
							points = new Polygon2D(size1, vec1);
#pragma endregion
							p = new Vector3(i2);
							q = new Vector3(i4);
#pragma region determinar size 2
							int size2 = 0;
							state = 0;
							aux = nullptr;
							bool continued = true;
							int k = 0;
							while(continued)
							{
								aux = &pol->points[k];
								switch (state)
								{
								case 0:
									{
										if(aux->equals(i2))
										{
											state++;
											size2++;
										}
									}
									break;
								case 1:
									{
										size2++;
										if(aux->equals(i4))
										{
											continued = false;
										}
									}
									break;
								}
								k++;
								if(k >= length)
								{
									continued = false;
								}
							}

							printf("size2 = %d\n", size2);
#pragma endregion

#pragma region determinar polígono 2
							state = 0;
							aux = nullptr;
							continued = true;
							k = 0;
							Vector3* vec2 = new Vector3[size2];
							kk = 0;
							while(continued)
							{
								aux = &pol->points[k];
								switch (state)
								{
								case 0:
									{
										if(aux->equals(i2))
										{
											state++;
											vec2[kk++] = Vector3(aux);
										}
									}
									break;
								case 1:
									{
										vec2[kk++] = Vector3(aux);
										if(aux->equals(i4))
										{
											continued = false;
										}
									}
									break;
								}
								k++;
								if(k >= length)
								{
									continued = false;
								}
							}
#pragma endregion
							points2 = new Polygon2D(size2, vec2);

							splitLine = true;
							solved = true;
						}
					}
					i++;
					if(i == length)
					{
						solved = true;
					}
				}
			}
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

	//Desenhar a área de desenho
	glBegin(GL_LINES);
	for(int j = 0; j < qtt; j++)
		{
			Polygon2D* pol = &polygons[j];
			Vector3* color = &pol->color;
			int length = pol->length;
			for (int i = 0; i < length; i++)
			{
				glColor3f(color->x, color->y, color->z);
				glVertex3f(pol->edges[i].o.x, pol->edges[i].o.y, 0.f);
				glVertex3f(pol->edges[i].p.x, pol->edges[i].p.y, 0.f);
			}
	}

	if(splitLine)
	{
		glColor3f(.0f, .0f, 1.f);
		glVertex3f(p->x, p->y, 0.f);
		glVertex3f(q->x, q->y, 0.f);

		int length = points->length;
		Vector3* color = &points->color;
		for (int i = 0; i < length; i++)
		{
			glColor3f(color->x, color->y, color->z);
			glVertex3f(points->edges[i].o.x, points->edges[i].o.y, 0.f);
			glVertex3f(points->edges[i].p.x, points->edges[i].p.y, 0.f);
		}

		length = points2->length;
		color = &points2->color;
		for (int i = 0; i < length; i++)
		{
			glColor3f(color->x, color->y, color->z);
			glVertex3f(points2->edges[i].o.x, points2->edges[i].o.y, 0.f);
			glVertex3f(points2->edges[i].p.x, points2->edges[i].p.y, 0.f);
		}
	}

	//Desenhar eixos
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-2.f, .0f, 0.f);
	glVertex3f( 2.f, .0f, 0.f);

	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(.0f, -2.f, 0.f);
	glVertex3f(.0f,  2.f, 0.f);
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

int main(void)
{
	srand (time(NULL));
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

	window = glfwCreateWindow(_width, _height, "Splitting Polygons", NULL, NULL);
	splitLine = false;
	qtt = 1;

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