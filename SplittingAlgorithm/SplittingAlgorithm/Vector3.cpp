#include "Vector3.h"

#include <stdio.h>
#include <math.h>

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

Vector3 Vector3::subtract(Vector3 another)
{
	return Vector3(x - another.x, y - another.y, z - another.z);
}

Vector3 Vector3::crossProduct(Vector3 another)
{
	float _x = y*another.z - z*another.y;
	float _y = z*another.x - x*another.z;
	float _z = x*another.y - y*another.x;
	
	return Vector3(_x, _y, _z);
}

void Vector3::normalize(void)
{
	float mag = x*x + y*y + z*z;
	mag = sqrt(mag);

	x = x/mag;
	y = y/mag;
	z = z/mag;
}

float Vector3::magnitude(void)
{
	float magnitude = sqrt(x*x + y*y + z*z);

	return magnitude;
}