#include "Polygon2d.h"

#include <stdio.h>

Polygon2D::Polygon2D(void)
{
	length = 0;
}

Polygon2D::Polygon2D(int length, Edge2d* edges)
{
	this->length = length;

	this->edges = new Edge2d[length];
	for (int i = 0; i < length; i++)
	{
		this->edges[i] = edges[i];
	}
}

Polygon2D Polygon2D::getBoundBox(void)
{
	float minX, maxX, minY, maxY;
	minX = minY =  99999999;
	maxX = maxY = -99999999;

	Edge2d edge;
	float x, y;
	for (int i = 0; i < length; i++)
	{
		edge = edges[i];
		x = edge.o.x;
		y = edge.o.y;

		if(x > maxX)
		{
			maxX = x;
		}
		if(y > maxY)
		{
			maxY = y;
		}
		if(x < minX)
		{
			minX = x;
		}
		if(y < minY)
		{
			minY = y;
		}

		x = edge.p.x;
		y = edge.p.y;

		if(x > maxX)
		{
			maxX = x;
		}
		if(y > maxY)
		{
			maxY = y;
		}
		if(x < minX)
		{
			minX = x;
		}
		if(y < minY)
		{
			minY = y;
		}
	}
	
	Edge2d* bounding = new Edge2d[4];
	bounding[0] = Edge2d(new Vector3(minX, maxY), new Vector3(maxX, maxY));
	bounding[1] = Edge2d(new Vector3(minX, minY), new Vector3(maxX, minY));
	bounding[2] = Edge2d(new Vector3(minX, minY), new Vector3(minX, maxY));
	bounding[3] = Edge2d(new Vector3(maxX, minY), new Vector3(maxX, maxY));

	return Polygon2D(4, bounding);
}

void Polygon2D::printConsole(void)
{
	printf("Polygon\n");

	for (int i = 0; i < length; i++)
	{
		this->edges[i].printConsole();
	}
}