#include "Vector3.h"

#include <stdio.h>

Vector3::Vector3(void)
{
	x = -1;
	y = -1;
	z = -1;
}

Vector3::Vector3(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0.f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(Vector3* copy)
{
	this->x = copy->x;
	this->y = copy->y;
	this->z = copy->z;
}

void Vector3::printConsole(void)
{
	printf("V: %f %f %f\n", x, y, z);
}

float Vector3::dotProduct(Vector3 another)
{
	return x*another.x + y*another.y;
}

bool Vector3::equals(Vector3 another)
{
	return x == another.x && y == another.y;
}