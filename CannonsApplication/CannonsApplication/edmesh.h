#ifndef __ED_MESH__
#define __ED_MESH__

#include "geometricObjects.h"
#include "edgeom.h"

class EDMesh : public GObject
{
public:
	float* triangles;
	int trianglesCount;
	float* normals;

	EDPoint min;
private:

public:
	EDMesh(const char* identifier);
	EDMesh(const char* identifier, char* path, char* filename);
	~EDMesh(void);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);
private:
	
};

#endif