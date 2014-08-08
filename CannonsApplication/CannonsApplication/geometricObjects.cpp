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

	glBegin(GL_QUADS);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, baseAmbientMaterial);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, baseDiffuseMaterial);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0f);

		glVertex3f(x, y, z);
		glVertex3f(x + width, y, z);
		glVertex3f(x + width, y, z + height);
		glVertex3f(x, y, z + height);
	glEnd();
}

void GPlane::update(float elapsedTime)
{ }