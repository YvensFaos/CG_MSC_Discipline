#ifndef __ED_MESH__
#define __ED_MESH__

#include "geometricObjects.h"
#include "edgeom.h"

class EDMesh : public GObject
{
public:
	EDTriangle* triangles;
	EDPoint min;
	int trianglesCount;
private:

public:
	EDMesh(const char* identifier);
	EDMesh(const char* identifier, char* path, char* filename);
	~EDMesh(void);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);

	void translate(EDPoint toPoint);
	void rotate(EDPoint axis, float angle);
	void scale(EDPoint axis, float factor);
	void updateMinValue(void);
private:
};

#endif