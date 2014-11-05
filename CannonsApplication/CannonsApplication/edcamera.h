#ifndef __ED_CAMERA__
#define __ED_CAMERA__

#include "edgeom.h"
#include "GeometricObjects.h"

enum Movement
{
	FORWARD, BACKWARD, LEFT, RIGHT, RUP, RDOWN, UP, DOWN, RLEFT, RRIGHT, AWAY, ONWARD, CLOSER, FARTHER
};

class EDCamera;

typedef void (*updateCameraCallbackFunction)(float elapsedTime, EDCamera* self);

class EDCamera
{
protected:
	updateCameraCallbackFunction updateCameraCallback;
public:
	int index;
	int pathLength;
	bool cycle;

	int intCounter;
	float floatCounter;
	float timer;
	int majorTriangles;
	int minorTriangles;

	float pNear;
	float pFar; 
	float pFOV;
	float angle;

	EDPoint* position;
	EDPoint* lookAt;
	EDPoint* up;
	int rotation;
public:
	EDCamera(void);
	EDCamera(EDPoint* position, EDPoint* lookAt, float pNear, float pFar, float pFOV);
	~EDCamera(void);

	void print(void);

	void move(Movement movement);
	void move(Movement movement, float size);
	void rotate(float angle);
	void cameraLookAt(void);
	void zoomIn(void);
	void zoomOut(void);
	void zoom(float value);

	void translateTo(EDPoint* toTranslate);
	void rotateToLookAt(EDPoint* axis, float angle);
	void rotateToPosition(EDPoint* axis, float angle);

	void callUpdate(float elapsedTime, EDCamera* self);
	void setCallUpdate(updateCameraCallbackFunction function);

private:
	void initializeValues(EDPoint* position, EDPoint* lookAt, float pNear, float pFar, float pFOV);
};

#endif