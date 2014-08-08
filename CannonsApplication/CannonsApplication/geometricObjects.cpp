#include "geometricObjects.h"

#include "GLFW\glfw3.h"

GPlane::GPlane(void)
{
	initialize(0.0f, 0.0f, nullptr, nullptr);
}

GPlane::GPlane(float height, float width, EDPoint* position, EDPlane* plane)
{
	initialize(height, width, position, plane);
}

GPlane::~GPlane(void)
{
	if(position)
		delete position;
	if(plane)
		delete plane;
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
	glBegin(GL_QUADS);


	glEnd();
}