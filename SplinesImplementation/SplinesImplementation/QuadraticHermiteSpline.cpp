#include "QuadraticHermiteSpline.h"

#include "GLFW\glfw3.h"
#include <stdio.h>

QuadraticHermite::QuadraticHermite(): EDSpline()
{ 
	p0  = 0;
	p1  = 1;
	p1l = 2;
}

QuadraticHermite::~QuadraticHermite()
{
	if(points != nullptr)
	{
		delete[] points;
	}
}

void QuadraticHermite::setPoints(Vector3* points, int size)
{
	this->points = new Vector3[size];
	for (int i = 0; i < size; i++)
	{
		this->points[i] = Vector3(points[i]);
	}
}

void QuadraticHermite::drawSpline(int steps)
{
	drawPoint(&points[p0]);

	float step = 1/(float)steps;

	float value = step;
	float value2 = value*value;
	float h0 = 0;
	float h1 = 0;
	float h2 = 0;

	float x = 0;
	float y = 0;

	while(value <= 1)
	{
		h0 = value2 - 2*value + 1;
		h1 = -1*value2 + 2*value;
		h2 = value2 - value;

		x = h0*points[p0].x + h1*points[p1].x + h2*points[p1l].x;
		y = h0*points[p0].y + h1*points[p1].y + h2*points[p1l].y;

		drawPoint(new Vector3(x,y,0.f));
		value += step;
		value2 = value*value;
	}

	drawPoint(&points[p1]);
}