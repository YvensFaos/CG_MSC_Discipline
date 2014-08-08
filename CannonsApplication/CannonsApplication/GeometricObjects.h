#ifndef __GEOMETRIC_OBJECTS__
#define __GEOMETRIC_OBJECTS__

#include "edgeom.h"

class GPlane
{
	public:
		float height;
		float width;
		EDPoint* position;
		EDPlane* plane;

		GPlane(void);
		GPlane(float height, float width, EDPoint* position, EDPlane* plane);
		~GPlane(void);

		void initialize(float height, float width, EDPoint* position, EDPlane* plane);
		void draw(void);
};

class GLine
{
	public:
};

class GSPhere
{
	public:
};

#endif