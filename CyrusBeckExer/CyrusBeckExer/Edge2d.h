#ifndef __EDGE_2D__
#define __EDGE_2D__

#include "Vector3.h"

class Edge2d
{
public:
	Vector3 o;
	Vector3 p;

	Edge2d(void);
	Edge2d(Vector3 o, Vector3 p);
	Edge2d(Edge2d* copy);

	Vector3 parametric(float t);
};

#endif