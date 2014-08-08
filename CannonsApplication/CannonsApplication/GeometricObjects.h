#ifndef __GEOMETRIC_OBJECTS__
#define __GEOMETRIC_OBJECTS__

#include "edgeom.h"
#include "GLFW\glfw3.h"

class GObject
{
public:
	static GLfloat baseAmbientMaterial[];
	static GLfloat baseDiffuseMaterial[];

	const char* identifier;
	GObject(const char* identifier)
	{
		this->identifier = identifier;
	}
	~GObject(void)
	{
		if(identifier)
		{
			delete identifier;
		}
	}

	virtual void draw(void) = 0;
	virtual void update(float elapsedTime) = 0;
};

class GPlane : GObject
{
public:
	float height;
	float width;
	EDPoint* position;
	EDPlane* plane;

	GPlane(const char* identifier);
	GPlane(const char* identifier, float height, float width, EDPoint* position, EDPlane* plane);
	~GPlane(void);

	void initialize(float height, float width, EDPoint* position, EDPlane* plane);
	void draw(void);
	void update(float elapsedTime);
};

/*
class GLine : GObject
{
public:
};

class GSPhere : GObject
{
public:
};


class GMesh : GObject
{
public:
};
*/
#endif