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

GCube::GCube(const char* identifier) : GObject(identifier)
{ }

GCube::GCube(const char* identifier, EDPoint* min, EDPoint* max) : GObject(identifier)
{ 
	initialize(min, max);
}

GCube::GCube(const char* identifier, EDPoint* min, float size) : GObject(identifier)
{
	initialize(min, new EDPoint(min->x + size, min->y + size, min->z + size));
}

void GCube::initialize(EDPoint* min, EDPoint* max)
{
	this->min = new EDPoint(min->x, min->y, min->z);
	this->position = this->min;
	this->max = new EDPoint(max->x, max->y, max->z);
}

GCube::~GCube(void)
{
	if(min)
		delete min;
	if(max)
		delete max;
}

void GCube::updateMinMax(EDPoint* min, EDPoint* max)
{
	initialize(min, max);
}

void GCube::draw(void)
{
	float xm,ym,zm;
	xm = min->x;
	ym = min->y;
	zm = min->z;

	float xx,yx,zx;
	xx = max->x;
	yx = max->y;
	zx = max->z;

	glBegin(GL_QUADS);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMaterial);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);

		glVertex3f(xm, ym, zm);
		glVertex3f(xm, yx, zm);
		glVertex3f(xm, yx, zx);
		glVertex3f(xm, ym, zx);

		glVertex3f(xx, ym, zm);
		glVertex3f(xx, yx, zm);
		glVertex3f(xx, yx, zx);
		glVertex3f(xx, ym, zx);

		glVertex3f(xm, ym, zm);
		glVertex3f(xx, ym, zm);
		glVertex3f(xx, ym, zx);
		glVertex3f(xm, ym, zx);

		glVertex3f(xm, yx, zm);
		glVertex3f(xx, yx, zm);
		glVertex3f(xx, yx, zx);
		glVertex3f(xm, yx, zx);

		glVertex3f(xm, ym, zm);
		glVertex3f(xx, ym, zm);
		glVertex3f(xx, yx, zm);
		glVertex3f(xm, yx, zm);

		glVertex3f(xm, ym, zx);
		glVertex3f(xx, ym, zx);
		glVertex3f(xx, yx, zx);
		glVertex3f(xm, yx, zx);
	glEnd();
}

void GCube::update(float elapsedTime)
{ }