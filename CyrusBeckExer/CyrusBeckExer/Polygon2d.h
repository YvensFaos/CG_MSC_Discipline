#ifndef __POLYGON_2D__
#define __POLYGON_2D__

#include "Edge2d.h"

class Polygon2D
{
	int lenght;
	Edge2d* edges;

	Polygon2D(void);
	Polygon2D(int lenght, Edge2d* edges);
};

#endif