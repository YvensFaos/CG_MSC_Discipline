#ifndef __POLYGON_2D__
#define __POLYGON_2D__

#include "Edge2d.h"

class Polygon2D
{
public:
	int length;
	bool isBoundingBox;
	Edge2d* edges;
	Vector3* points;
	Vector3* normals;
	Vector3 center;
	Polygon2D* bounding;
	Vector3 lower;
	Vector3 upper;
	Vector3 minorDiagonal;
	Vector3 majorDiagonal;

	Polygon2D(void);
	Polygon2D(int length, Vector3* points);
	Polygon2D(int length, Edge2d* edges);
	Polygon2D(int length, Edge2d* edges, bool bounding);

	void defaultConstructor(int length, Edge2d* edges);
	void generateBoundBox(void);
	void printConsole(void);
	void calculateOuter(void);
	void translate(float x, float y);
	bool collide(Polygon2D* another);

	Polygon2D getBoundBox(void);
};

#endif