#include "EDSpline.h"

#include <stdio.h>

EDSpline::EDSpline()
{

}

void EDSpline::drawPoint(Vector3* point)
{
	float size = 0.0125f;
	glBegin(GL_QUADS);
	glColor3f(point->x, point->y, 0.2);

	glVertex3f(point->x - size, point->y - size, point->z);
	glVertex3f(point->x + size, point->y - size, point->z);
	glVertex3f(point->x + size, point->y + size, point->z);
	glVertex3f(point->x - size, point->y + size, point->z);
	glEnd();
}
