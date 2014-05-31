#ifndef __ED_SPLINE__
#define __ED_SPLINE__

#include "Vector3.h"
#include "GLFW\glfw3.h"

class EDSpline
{
protected:
	Vector3* points;

public:
	EDSpline();
	virtual ~EDSpline() {};
	virtual void setPoints(Vector3* points, int size) = 0;
	virtual void drawSpline(int steps) = 0;
	void drawPoint(Vector3* point);
};
#endif