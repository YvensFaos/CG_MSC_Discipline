#include "Vector3.h"

Vector3::Vector3(void)
{
	x = -1;
	y = -1;
	z = -1;
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