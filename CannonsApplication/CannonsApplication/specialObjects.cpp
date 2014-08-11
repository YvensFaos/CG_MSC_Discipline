#include "specialObjects.h"

#include <stdio.h>

CannonBall::CannonBall(const char* identifier) : GObject(identifier) 
{ }

CannonBall::CannonBall(const char* identifier, EDPoint* targets, int length, float size) : GObject(identifier)
{
	initialize(targets, length, size);
}

CannonBall::~CannonBall(void)
{
	if(targets)
		delete targets;
}

void CannonBall::initialize(EDPoint* targets, int length, float size)
{
	this->size = size;
	this->floatCounter = 0.0f;
	//Aponta para o próximo índice
	this->index = 1;

	this->length = length;
	this->targets = new EDPoint[length];
	for (int i = 0; i < length; i++)
	{
		this->targets[i] = EDPoint(targets[i].x, targets[i].y, targets[i].z);
	}
	actualPosition = new EDPoint(targets[0].x, targets[0].y, targets[0].z);
	params = new float[3];
	//Posição inicial
	params[0] = actualPosition->y;
	params[1] = 23.0f;
	params[2] = 0.0f;

	EDPoint* min = &this->targets[0];
	float x,y,z;
	x = min->x + size;
	y = min->y + size;
	z = min->z + size;
	EDPoint* max = new EDPoint(x,y,z);

	char cubeIdentifier[256];
	sprintf_s(cubeIdentifier, "%s%s", identifier, "-cube");

	cube = new GCube(cubeIdentifier, min, max);
}

void CannonBall::setMaterial(GLfloat* ambient, GLfloat* diffuse)
{
	cube->setMaterial(ambient, diffuse);
}

void CannonBall::draw(void)
{
	cube->draw();
}

void CannonBall::update(float elapsedTime)
{
	float dx = position->x - targets[index].x;
	if(dx < 0) dx *= -1;
	float dz = position->z - targets[index].z;
	if(dz < 0) dz *= -1;

	if(dx <= 0.1f && dz <= 0.1f)
	{
		actualPosition = new EDPoint(targets[index].x, targets[index].y, targets[index].z);
		index = (++index)%length;
		floatCounter = 0.0f;

		params[0] = actualPosition->y;
		params[2] = 0.0f;
	}
	else
	{
		float x,y,z;

		float s = 0.0f;
		//s = s0 + v0*t + a/2 * t^2
		s = params[0] + params[1]*params[2] - 5.0f*(params[2]*params[2]);

		x = actualPosition->x + (targets[index].x - actualPosition->x)*floatCounter;
		y = s;
		z = actualPosition->z + (targets[index].z - actualPosition->z)*floatCounter;

		floatCounter += elapsedTime*0.0105f;
		params[2] += elapsedTime*0.05f;

		EDPoint* min = new EDPoint(x,y,z);
		position = new EDPoint(x,y,z);

		x = min->x + size;
		y = min->y + size;
		z = min->z + size;
		EDPoint* max = new EDPoint(x,y,z);
		cube->updateMinMax(min, max);

	}
}