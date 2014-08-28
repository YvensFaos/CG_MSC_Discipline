#ifndef __ED_MESH__
#define __ED_MESH__

#include "geometricObjects.h"
#include "edgeom.h"

class EDMesh : public GObject
{
public:
	EDTriangle* triangles;
	int trianglesCount;
	float* normals;
private:

public:
	EDMesh(const char* identifier);
	EDMesh(const char* identifier, char* path, char* filename);
	~EDMesh(void);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);

	void translate(EDPoint toPoint);
private:
	void calculateNormals(void);
};

#endif