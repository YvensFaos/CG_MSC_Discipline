#ifndef __ED_MESH__
#define __ED_MESH__

#include "geometricObjects.h"
#include "edgeom.h"

class EDMesh : public GObject
{
public:
	EDTriangles* triangles;
	int trianglesCount;
	float* normals;

private:

public:
	EDMesh(void);
	EDMesh(char* path, char* filename);
	~EDMesh(void);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);
};

#endif