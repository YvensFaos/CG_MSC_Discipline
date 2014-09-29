#ifndef __ED_MESH__
#define __ED_MESH__

#include "geometricObjects.h"
#include "edgeom.h"

#include <vector>

class EDMesh : public GObject
{
public:
	EDTriangle* triangles;
	EDPoint min;
	EDPoint center;
	int trianglesCount;

	std::vector<EDTriangle*> trianglesVector;
private:

public:
	EDMesh(void);
	EDMesh(const char* identifier);
	EDMesh(const char* identifier, char* path, char* filename);
	EDMesh(const char* identifier, std::vector<EDTriangle*> triangles);
	~EDMesh(void);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);

	void translate(EDPoint toPoint);
	void rotate(EDPoint axis, float angle);
	void scale(EDPoint axis, float factor);
	void updateMinValue(void);
	void calculateCenter(void);

	void initializeByVector(void);
private:
};

#endif