#ifndef __CUBIC_HERMITE_SPLINE__
#define __CUBIC_HERMITE_SPLINE__

#include "EDSpline.h"
#include "Vector3.h"

class CubicHermite : public EDSpline
{
private:
	int p0;
	int p1;
	int p0l;
	int p1l;
public:
	CubicHermite();
	~CubicHermite();

	void setPoints(Vector3* points, int size);
	void drawSpline(int steps);
};

#endif