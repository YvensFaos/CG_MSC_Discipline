#include "Edge2d.h"

Edge2d::Edge2d(void)
{
	o = new Vector3();
	p = new Vector3();
}

Edge2d::Edge2d(Vector3 o, Vector3 p)
{
	this->o = new Vector3(&o);
	this->p = new Vector3(&p);
}

Edge2d::Edge2d(Edge2d* copy)
{
	this->o = new Vector3(&copy->o);
	this->p = new Vector3(&copy->p);
}

Vector3 Edge2d::parametric(float t)
{
	float x = o.x + (p.x - o.x)*t;
	float y = o.y + (p.y - o.y)*t;
	float z = o.z + (p.z - o.z)*t;

	return new Vector3(x,y,z);
}