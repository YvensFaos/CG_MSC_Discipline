#include "GLFW\glfw3.h"

GLFWwindow* window;

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if(key == GLFW_KEY_ESCAPE)
	{
		if(action == GLFW_PRESS) {
			if (key == GLFW_KEY_ESCAPE) {
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
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
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
		glColor4f(1.f, 1.f, .3f, .5f);
		glVertex3f(-0.8, -0.4f, 0.f);
		glVertex3f(-0.8,  0.4f, 0.f);
		glVertex3f( 0.8,  0.4f, 0.f);
		glVertex3f( 0.8, -0.4f, 0.f);
	glEnd();

	glBegin(GL_LINE);
	glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.2, 1.f, 0.f);
		glVertex3f(.6, -.2f, 0.f);
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

	window = glfwCreateWindow(640, 480, "Cohen Sutherland", NULL, NULL);

	if (!window)
    {
        glfwTerminate();
        return 0;
    }

	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 80, 120);
	glfwSetKeyCallback(window, glfwKeyCallback);

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