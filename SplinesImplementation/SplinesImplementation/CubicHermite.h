#ifndef __CUBIC_HERMITE_SPLINE__
#define __CUBIC_HERMITE_SPLINE__

#include "EDSpline.h"
#include "Vector3.h"

<<<<<<< HEAD
class QuadraticHermite : public EDSpline
=======
class CubicHermite : public EDSpline
>>>>>>> a43ff965a6bb4ed16ff275f31825183378ed49a7
{
private:
	int p0;
	int p1;
<<<<<<< HEAD
	int p1l;
public:
	QuadraticHermite();
	~QuadraticHermite();
=======
	int p0l;
	int p1l;
public:
	CubicHermite();
	~CubicHermite();
>>>>>>> a43ff965a6bb4ed16ff275f31825183378ed49a7

	void setPoints(Vector3* points, int size);
	void drawSpline(int steps);
};

#endif