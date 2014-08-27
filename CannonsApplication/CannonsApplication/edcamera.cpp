#include "edcamera.h"

#include <stdio.h>
#include <GL\glut.h>

#define pi180  3.14159265f/180.0f
#define sizeStep 0.1f
#define zoomStep 0.125f

EDCamera::EDCamera(void)
{
	initializeValues(nullptr, nullptr, 0.0f, 0.0f, 0.0f);
}

EDCamera::EDCamera(EDPoint* position, EDPoint* lookAt, float pNear, float pFar, float pFOV)
{
	initializeValues(position, lookAt, pNear, pFar, pFOV);
}

EDCamera::~EDCamera(void)
{
	if(position)
		delete position;
	if(lookAt)
		delete lookAt;
}

void EDCamera::print(void)
{
	printf("Position %f %f %f\nLook At %f %f %f\nRotation: %d\n", position->x, position->y, position->z, lookAt->x, lookAt->y, lookAt->z, rotation);
}

void EDCamera::move(Movement movement)
{
	switch(movement)
	{
	case FORWARD:
		{
			position->z -= sizeStep;
			lookAt->z -= sizeStep;
		}
		break;
	case BACKWARD:
		{
			position->z += sizeStep;
			lookAt->z += sizeStep;
		}
		break;
	case LEFT:
		{
			position->x -= sizeStep;
			lookAt->x -= sizeStep;
		}
		break;
	case RIGHT:
		{
			position->x += sizeStep;
			lookAt->x += sizeStep;
		}
		break;
	case RUP:
		{
			position->y += .2f;
		}
		break;
	case RDOWN:
		{
			position->y -= .2f;
		}
		break;
	case RLEFT:
		{
			rotate(-10.0f);
		}
		break;
	case RRIGHT:
		{
			rotate( 10.0f);
		}
		break;
	case UP:
		{
			position->y += sizeStep;
			lookAt->y += sizeStep;
		}
		break;
	case DOWN:
		{
			position->y -= sizeStep;
			lookAt->y -= sizeStep;
		}
		break;
	}	
}

void EDCamera::rotate(float angle)
{
	if(angle == 0)
	{
		return;
	}

	angle = angle*pi180;

	float cosa = cos(angle);
	float sina = sin(angle);

	float xV = position->x;
	float zV = position->z;

	lookAt->x -= xV;
	lookAt->z -= zV;

	float _xV = lookAt->x;
	float _zV = lookAt->z;

	lookAt->x = _xV*cosa - _zV*sina;
	lookAt->z = _xV*sina + _zV*cosa;

	lookAt->x += xV;
	lookAt->z += zV;
}

void EDCamera::initializeValues(EDPoint* position, EDPoint* lookAt, float pNear, float pFar, float pFOV)
{
	this->position = position;
	this->lookAt = lookAt;
	this->pNear = pNear;
	this->pFar = pFar;
	this->pFOV = pFOV;
}

void EDCamera::cameraLookAt(void)
{
	gluLookAt(
	position->x, position->y, position->z, 
	lookAt->x, lookAt->y, lookAt->z, 
	0, 1, 0);
}

void EDCamera::zoomIn(void)
{
	zoom(-zoomStep);
}

void EDCamera::zoomOut(void)
{
	zoom(zoomStep);
}

void EDCamera::zoom(float value)
{
	pFOV += value;
}
