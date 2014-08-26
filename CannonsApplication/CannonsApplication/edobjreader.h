#ifndef __ED_OBJ_READER__
#define __ED_OBJ_READER__

#include "edgeom.h"

class EDObjReader
{
public:
	EDPoint* vertexesArray;
	int vertexesSize;

	EDTriangle* triangles;
	int trianglesSize;

	EDObjReader(char* path, char* filename);
	~EDObjReader(void);
};

#endif