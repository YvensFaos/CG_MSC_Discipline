#include "geometricObjects.h"

#include <stdio.h>

GLfloat GObject::baseAmbientMaterial[] = {.9f, .1f,  .3f, 1.0f};
GLfloat GObject::baseDiffuseMaterial[] = {.9f, .05f, .3f, 1.0f};

GPlane::GPlane(const char* identifier) : GObject(identifier)
{
	initialize(0.0f, 0.0f, nullptr, nullptr);
}

GPlane::GPlane(const char* identifier, float height, float width, EDPoint* position, EDPlane* plane) : GObject(identifier)
{
	initialize(height, width, position, plane);
}

GPlane::~GPlane(void)
{
	if(position)
	{
		delete position;
	}
	if(plane)
	{
		delete plane;
	}
}

void GPlane::initialize(float height, float width, EDPoint* position, EDPlane* plane)
{
	this->height = height;
	this->width = width;
	this->position = position;
	this->plane = plane;
}

void GPlane::draw(void)
{
	float x,y,z;
	x = position->x;
	y = position->y;
	z = position->z;

	GLfloat ambient[] = {.3f, .9f, .1f, 1.f};
	GLfloat diffuse[] = {.7f, .7f, .1f, 1.f};

	glBegin(GL_QUADS);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);

		//glColor3f(0.2f, 0.2f, 0.4f);
		glVertex3f(x, y, z);
		glVertex3f(x + width, y, z);
		glVertex3f(x + width, y, z + height);
		glVertex3f(x, y, z + height);
	glEnd();
}

void GPlane::update(float elapsedTime)
{ }