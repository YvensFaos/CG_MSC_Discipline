#include "CubicHermite.h"

#include "GLFW\glfw3.h"
#include <stdio.h>

CubicHermite::CubicHermite(): EDSpline()
{ 
	p0  = 0;
	p1  = 1;
	p0l = 2;
	p1l = 3;
}

CubicHermite::~CubicHermite()
{
	if(points != nullptr)
	{
		delete[] points;
	}
}

void CubicHermite::setPoints(Vector3* points, int size)
{
	this->points = new Vector3[size];
	for (int i = 0; i < size; i++)
	{
		this->points[i] = Vector3(points[i]);
	}
}

void CubicHermite::drawSpline(int steps)
{
	drawPoint(&points[p0]);

	float step = 1/(float)steps;

	float value = step;
	float value2 = value*value;
	float value3 = value2*value;
	float h0 = 0;
	float h1 = 0;
	float h2 = 0;
	float h3 = 0;

	float x = 0;
	float y = 0;

	while(value <= 1)
	{
		h0 = 2*value3 - 3*value2 + 1;
		h1 = -2*value3 + 3*value2;
		h2 = value3 - 2*value2 + value;
		h3 = value3 - value2;

		x = h0*points[p0].x + h1*points[p1].x + h2*points[p0l].x + h3*points[p1l].x;
		y = h0*points[p0].y + h1*points[p1].y + h2*points[p0l].y + h3*points[p1l].y;

		drawPoint(new Vector3(x,y,0.f));
		value += step;
		value2 = value*value;
		value3 = value2*value;
	}

	drawPoint(&points[p1]);
}