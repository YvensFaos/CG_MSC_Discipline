#include "geometricObjects.h"

#include <stdio.h>

GLfloat GObject::baseAmbientMaterial[] = {.4f, .4f, .3f, 1.0f};
GLfloat GObject::baseDiffuseMaterial[] = {.2f, .2f, .3f, 1.0f};

void emptyFunction(float elapsedTime, GObject* object) { }

GObject::GObject(const char* identifier)
{
	this->identifier = identifier;
	intCounter = 0;
	floatCounter = 0.0f;
	ambientMaterial = new GLfloat[4];
	diffuseMaterial = new GLfloat[4];
	setMaterial(baseAmbientMaterial, baseDiffuseMaterial);

	position = new EDPoint(0.0f, 0.0f, 0.0f);

	setCallUpdate(emptyFunction);
}

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
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMaterial);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);

		glVertex3f(x, y, z);
		glVertex3f(x + width, y, z);
		glVertex3f(x + width, y, z + height);
		glVertex3f(x, y, z + height);
	glEnd();
}

void GPlane::update(float elapsedTime)
{ }