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
	printf("Position %f %f %f\nLook At %f %f %f\nRotation: %d\nField of View: %f\n\n", position->x, position->y, position->z, lookAt->x, lookAt->y, lookAt->z, rotation, pFOV);
}

void EDCamera::move(Movement movement, float size)
{
	switch(movement)
	{
	case FARTHER:
	{
		EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
		direction = *direction.makeUnitary();
		direction.multiply(size);

		lookAt->sum(&direction);
	}
	break;
	case CLOSER:
	{
		EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
		direction = *direction.makeUnitary();
		direction.multiply(-1*size);

		lookAt->sum(&direction);
	}
	break;
	case ONWARD:
		{
			EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
			direction = *direction.makeUnitary();
			direction.multiply(size);

			position->sum(&direction);
		}
		break;
	case AWAY:
		{
			EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
			direction = *direction.makeUnitary();
			direction.multiply(-1*size);

			position->sum(&direction);
		}
		break;
	case FORWARD:
		{
			EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
			direction = *direction.makeUnitary();
			direction.multiply(size);

			position->sum(&direction);
			lookAt->sum(&direction);
		}
		break;
	case BACKWARD:
		{
			EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
			direction = *direction.makeUnitary();
			direction.multiply(-1*size);

			position->sum(&direction);
			lookAt->sum(&direction);
		}
		break;
	case LEFT:
		{
			EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
			direction = *direction.makeUnitary();
			EDPoint sizer = EDPoint::crossProduct(up, &direction);
			sizer = *sizer.makeUnitary();
			sizer.multiply(size);

			position->sum(&sizer);
			lookAt->sum(&sizer);
		}
		break;
	case RIGHT:
		{
			EDPoint direction = EDPoint(lookAt->x - position->x, lookAt->y - position->y, lookAt->z - position->z);
			direction = *direction.makeUnitary();
			EDPoint sizer = EDPoint::crossProduct(up, &direction);
			sizer = *sizer.makeUnitary();
			sizer.multiply(-1*size);

			position->sum(&sizer);
			lookAt->sum(&sizer);
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
			EDPoint direction = EDPoint(up->x, up->y, up->z);
			direction = *direction.makeUnitary();
			direction.multiply(size);

			position->sum(&direction);
			lookAt->sum(&direction);
		}
		break;
	case DOWN:
		{
			EDPoint direction = EDPoint(up->x, up->y, up->z);
			direction = *direction.makeUnitary();
			direction.multiply(-1*size);

			position->sum(&direction);
			lookAt->sum(&direction);
		}
		break;
	}	
}

void EDCamera::move(Movement movement)
{
	move(movement, sizeStep);
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

void EDCamera::callUpdate(float elapsedTime, EDCamera* self)
{
	(updateCameraCallback)(elapsedTime, self);
}

void EDCamera::setCallUpdate(updateCameraCallbackFunction function)
{
	updateCameraCallback = function;
}

void EDCamera::translateTo(EDPoint* toPoint)
{
	this->position->translateTo(toPoint);
	this->lookAt->translateTo(toPoint);
}

void EDCamera::initializeValues(EDPoint* position, EDPoint* lookAt, float pNear, float pFar, float pFOV)
{
	this->position = position;
	this->lookAt = lookAt;
	this->pNear = pNear;
	this->pFar = pFar;
	this->pFOV = pFOV;

	up = new EDPoint(0.0f, 1.0f, 0.0f);
}

void EDCamera::rotateToLookAt(EDPoint* axis, float angle)
{
	position->rotateTo(lookAt, *axis, angle);
}

void EDCamera::rotateToPosition(EDPoint* axis, float angle)
{
	lookAt->rotateTo(position, *axis, angle);
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
