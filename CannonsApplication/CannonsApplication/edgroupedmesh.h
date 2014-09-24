#ifndef __ED_GROUPED_MESH__
#define __ED_GROUPED_MESH__

#include <hash_map>
#include <string>

#include "edmesh.h"

class EDGroupedMesh : public GObject
{
public:
	std::hash_map<std::string, EDMesh> meshes;
	std::vector<std::string> groups;

public:
	EDGroupedMesh(const char* identifier);
	EDGroupedMesh(const char* identifier, char* path, char* filename);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);

	void translate(EDPoint toPoint);
	void rotate(EDPoint axis, float angle);
	void scale(EDPoint axis, float factor);
	void updateMinValue(void);
};

#endif