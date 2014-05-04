#include "Polygon2d.h"

#include <stdio.h>

Polygon2D::Polygon2D(void)
{
	length = 0;
}

Polygon2D::Polygon2D(int length, Edge2d* edges)
{
	defaultConstructor(length, edges);

	generateBoundBox();
}

Polygon2D::Polygon2D(int length, Edge2d* edges, bool bounding)
{
	defaultConstructor(length, edges);

	isBoundingBox = bounding;
	if(!isBoundingBox)
	{
		generateBoundBox();
	}
}

void Polygon2D::defaultConstructor(int length, Edge2d* edges)
{
	this->length = length;

	this->edges = new Edge2d[length];
	this->points = new Vector3[length];
	this->normals = new Vector3[length];

	for (int i = 0; i < length; i++)
	{
		this->edges[i] = edges[i];
		this->points[i] = edges[i].o;
	}

	isBoundingBox = false;
}

void Polygon2D::generateBoundBox(void)
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
	
	Edge2d* boundingEdges = new Edge2d[4];
	boundingEdges[0] = Edge2d(new Vector3(minX, maxY), new Vector3(maxX, maxY));
	boundingEdges[1] = Edge2d(new Vector3(minX, minY), new Vector3(maxX, minY));
	boundingEdges[2] = Edge2d(new Vector3(minX, minY), new Vector3(minX, maxY));
	boundingEdges[3] = Edge2d(new Vector3(maxX, minY), new Vector3(maxX, maxY));

	bounding = new Polygon2D(4, boundingEdges, true);	
	minorDiagonal = Vector3(minX, minY);
	majorDiagonal = Vector3(maxX, maxY);
	center = Vector3((maxX + minX)/2.f, (maxY + minY)/2.f);
}

Polygon2D Polygon2D::getBoundBox(void)
{
	return *bounding;
}

void Polygon2D::printConsole(void)
{
	printf("Polygon:\nEdges:\n");

	for (int i = 0; i < length; i++)
	{
		this->edges[i].printConsole();
	}

	printf("Normals:\n");

	for(int i = 0; i < length; i++)
	{
		this->normals[i].printConsole();
	}

	printf("Points:\n");

	for (int i = 0; i < length; i++)
	{
		this->points[i].printConsole();
	}

	printf("Center:\n");

	this->center.printConsole();
}

void Polygon2D::calculateOuter(void)
{
	Edge2d edge;
	for(int i = 0; i < length; i++)
	{
		edge = this->edges[i];
		Vector3 direction = edge.p.subtract(edge.o);
		Vector3 zPerpendicular = Vector3(edge.o.x, 0, 1);

		normals[i] = direction.crossProduct(zPerpendicular);
		normals[i].normalize();
	}
}