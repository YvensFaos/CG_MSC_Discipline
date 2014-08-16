#include "geometricObjects.h"

#include <stdio.h>

GLfloat GObject::baseAmbientMaterial[] = {.4f, .4f, .3f, 1.0f};
GLfloat GObject::baseDiffuseMaterial[] = {.2f, .2f, .3f, 1.0f};

int GCube::LBN = 0;
int GCube::LTN = 1;
int GCube::RBN = 2;
int GCube::RTN = 3;
int GCube::LBF = 4;
int GCube::LTF = 5;
int GCube::RBF = 6;
int GCube::RTF = 7;

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

	points = new EDPoint[8];
	int i = 0;
	points[LBN] = *this->min;
	points[RBN] = EDPoint(max->x, min->y, min->z);
	points[RTN] = EDPoint(max->x, max->y, min->z);
	points[LTN] = EDPoint(min->x, max->y, min->z);
	points[LBF] = EDPoint(min->x, min->y, max->z);
	points[RBF] = EDPoint(max->x, min->y, max->z);
	points[RTF] = *this->max;
	points[LTF] = EDPoint(min->x, max->y, max->z);
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

		points[LBN].toVertex3f();
		points[LTN].toVertex3f();
		points[LTF].toVertex3f();
		points[LBF].toVertex3f();

		points[RBN].toVertex3f();
		points[RTN].toVertex3f();
		points[RTF].toVertex3f();
		points[RBF].toVertex3f();

		points[LBN].toVertex3f();
		points[RBN].toVertex3f();
		points[RBF].toVertex3f();
		points[LBF].toVertex3f();

		points[LTN].toVertex3f();
		points[RTN].toVertex3f();
		points[RTF].toVertex3f();
		points[LTF].toVertex3f();

		points[LBN].toVertex3f();
		points[RBN].toVertex3f();
		points[RTN].toVertex3f();
		points[LTN].toVertex3f();

		points[LBF].toVertex3f();
		points[RBF].toVertex3f();
		points[RTF].toVertex3f();
		points[LTF].toVertex3f();
	glEnd();
}

void GCube::update(float elapsedTime)
{ }

void GCube::translate(EDPoint* toTranslate)
{ 
	for(int i = 0; i < 8; i++)
	{
		points[i].x += toTranslate->x;
		points[i].y += toTranslate->y;
		points[i].z += toTranslate->z;
	}
}

void GCube::rotate(EDPoint* axis, float angle)
{ 
	angle = angle*pi180;

	float cosa = cos(angle);
	float sina = sin(angle);

	printf("x\n");
	print();
	EDPoint* minInitial = new EDPoint(points[LBN].x, points[LBN].y, points[LBN].z);
	translate(new EDPoint(-1*minInitial->x, -1*minInitial->y, -1*minInitial->z));

	printf("x\n");
	print();
	float xx = 0, yx = 0, zx = 0;
	for(int i = 0; i < 8; i++)
	{
		xx = points[i].x;
		yx = points[i].y;
		zx = points[i].z;

		if(axis->x != 0)
		{
			points[i].y = cosa*yx - sina*zx;
			points[i].z = sina*yx + sina*zx;
		}
		if(axis->y != 0)
		{
			points[i].x = cosa*xx + sina*zx;
			points[i].z = -sina*xx + cosa*zx;
		}
		if(axis->z != 0)
		{
			points[i].x = cosa*xx - sina*yx;
			points[i].y = sina*xx + sina*yx;
		}
	}
	printf("x\n");
	print();

	translate(new EDPoint(minInitial->x, minInitial->y, minInitial->z));
	printf("x\n");
	print();
}

void GCube::scale(EDPoint* axis, float factor)
{ 
	EDPoint* minInitial = new EDPoint(points[LBN].x, points[LBN].y, points[LBN].z);
	translate(new EDPoint(-1*minInitial->x, -1*minInitial->y, -1*minInitial->z));

	for(int i = 0; i < 8; i++)
	{
		if(axis->x != 0)
		{
			points[i].x *= factor;
		}
		if(axis->y != 0)
		{
			points[i].y *= factor;
		}
		if(axis->z != 0)
		{
			points[i].z *= factor;
		}
	}
	translate(new EDPoint(minInitial->x, minInitial->y, minInitial->z));
}

void GCube::print(void)
{
	for(int i = 0; i < 8; i++)
	{
		points[i].print();
	}
}