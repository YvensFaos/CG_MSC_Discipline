#ifndef __GEOMETRIC_OBJECTS__
#define __GEOMETRIC_OBJECTS__

#include "edgeom.h"
#include "GLFW\glfw3.h"
#include <GL\glut.h>

class GObject;

typedef void (*updateCallbackFunction)(float elapsedTime, GObject* object);

class GObject
{
protected:
	updateCallbackFunction updateCallback;
public:
	int intCounter;
	float floatCounter;
	float* params;

	static GLfloat baseAmbientMaterial[];
	static GLfloat baseDiffuseMaterial[];

	GLfloat* ambientMaterial;
	GLfloat* diffuseMaterial;

	EDPoint* position;
	
	const char* identifier;

	GObject(const char* identifier);
	~GObject(void)
	{ }

	virtual void draw(void) = 0;
	virtual void update(float elapsedTime) = 0;

	void callUpdate(float elapsedTime, GObject* object)
	{
		(updateCallback)(elapsedTime, object);
	}

	void setCallUpdate(updateCallbackFunction function)
	{
		updateCallback = function;
	}

	virtual void setMaterial(GLfloat* ambient, GLfloat* diffuse)
	{
		for(int i = 0; i < 4; i++)
		{
			ambientMaterial[i] = ambient[i];
			diffuseMaterial[i] = diffuse[i];
		}
	}
};

class GPlane : public GObject
{
public:
	float height;
	float width;
	
	EDPlane* plane;
	GPlane(const char* identifier);
	GPlane(const char* identifier, float height, float width, EDPoint* position, EDPlane* plane);
	~GPlane(void);

	void draw(void);
	void update(float elapsedTime);
private:
	void initialize(float height, float width, EDPoint* position, EDPlane* plane);
};

class GCube : public GObject
{
public:
	EDPoint* min;
	EDPoint* max;

	GCube(const char* identifier);
	GCube(const char* identifier, EDPoint* min, float size);
	GCube(const char* identifier, EDPoint* min, EDPoint* max);
	~GCube(void);

	void draw(void);
	void update(float elapsedTime);

	void updateMinMax(EDPoint* min, EDPoint* max);
private:
	void initialize(EDPoint* min, EDPoint* max);
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