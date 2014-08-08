#ifndef __ED_CAMERA__
#define __ED_CAMERA__

#include "edgeom.h"

enum Movement
{
	FORWARD, BACKWARD, LEFT, RIGHT, RUP, RDOWN, UP, DOWN, RLEFT, RRIGHT
};

class EDCamera
{
public:
	int index;
	int pathLength;
	bool cycle;

	int majorTriangles;
	int minorTriangles;

	float pNear;
	float pFar; 
	float pFOV;
	float angle;

	EDPoint* position;
	EDPoint* lookAt;
	int rotation;
public:
	EDCamera(void);
	EDCamera(EDPoint* position, EDPoint* lookAt, float pNear, float pFar, float pFOV);
	~EDCamera(void);

	void print(void);

	void move(Movement movement);
	void rotate(float angle);
	void cameraLookAt(void);
private:
	void initializeValues(EDPoint* position, EDPoint* lookAt, float pNear, float pFar, float pFOV);
};

#endif