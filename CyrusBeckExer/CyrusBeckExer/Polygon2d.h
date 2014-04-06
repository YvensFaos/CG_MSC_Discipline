#ifndef __POLYGON_2D__
#define __POLYGON_2D__

#include "Edge2d.h"

class Polygon2D
{
public:
	int length;
	Edge2d* edges;

	Polygon2D(void);
	Polygon2D(int length, Edge2d* edges);

	Polygon2D getBoundBox(void);
	void printConsole(void);
};

#endif