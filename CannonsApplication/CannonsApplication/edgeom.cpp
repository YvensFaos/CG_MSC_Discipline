#include "edgeom.h"

#include <stdio.h>

// EDPoint

EDPoint::EDPoint()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

EDPoint::EDPoint(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

EDPoint* EDPoint::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return this;
}

EDPoint* EDPoint::set(EDPoint* from)
{
	x = from->x;
	y = from->y;
	z = from->z;
	return this;
}

bool EDPoint::equals(EDPoint* b)
{
	return x == b->x && y == b->y && z == b->z;
}

bool EDPoint::almostEquals(EDPoint* b)
{
	return almostEquals(b, 0.001f);
}

bool EDPoint::almostEquals(EDPoint* b, float precision)
{
	float dx = b->x - x;
	float dy = b->y - y;
	float dz = b->z - z;
	if (dx < 0)
		dx *= -1.0f;
	if (dy < 0)
		dy *= -1.0f;
	if (dz < 0)
		dz *= -1.0f;
	const float delta = precision;
	return dx < delta && dy < delta && dz < delta;
}

void EDPoint::toVertex3f()
{
	glVertex3f(x, y, z);
}

EDPoint::~EDPoint(void)
{ 
	//printf("destruir\n");
}

float EDPoint::isMultiple(EDPoint* v)
{
	//Busca a primeira componente não nula
	float fx;
	if (v->x != 0){
		fx = x / v->x;
	}
	else if (v->y != 0){
		fx = y / v->y;
	}
	else if (v->z != 0){
		fx = z / v->z;
	}
	else{
		fx = 0;
	}

	//O fx representa quantas vezes o ponto v suspostamente é maior do que este ponto

	//Verifica se cada componente do ponto v multiplicada pelo fator fx e subtraída da componente do ponto resulta em 0
	float difx = x - v->x * fx;
	float dify = y - v->y * fx;
	float difz = z - v->z * fx;

	//Se o quadrado do somatório das diferenças for maior do que 0.0001f, logo, esses pontos não são múltiplos
	if (difx * difx + dify * dify + difz * difz < 0.0001f){
		return fx;
	}
	return 0;
}

EDPoint* EDPoint::setMiddle(EDPoint* a, EDPoint* b)
{
	x = (a->x + b->x) / 2.0f;
	y = (a->y + b->y) / 2.0f;
	z = (a->z + b->z) / 2.0f;
	return this;
}

float fastSqrt(const float x) 
{
	static union
	{
		int i;
		float x;
	} u;
	u.x = x;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22); 
	u.x = 0.5f * (u.x + x / u.x);
	return u.x;
}

// A simple cubic approximation, the Lagrange polynomial for x in {-1, -1/2, 0, 1/2, 1}
float fastACos(float x)
{
   return (-0.69813170079773212f * x * x - 0.87266462599716477f) * x + 1.5707963267948966f;
}

float fastSin(float x)
{
	// always wrap input angle to -PI..PI
	if (x < -3.14159265)
		x += 6.28318531;
	else if (x > 3.14159265)
		x -= 6.28318531;

	// compute sine
	if (x < 0)
		return 1.27323954 * x + .405284735 * x * x;
	else
		return 1.27323954 * x - 0.405284735 * x * x;
}

float fastCos(float x)
{
	// always wrap input angle to -PI..PI
	if (x < -3.14159265)
		x += 6.28318531;
	else if (x > 3.14159265)
		x -= 6.28318531;

	// compute cosine: sin(x + PI/2) = cos(x)
	x += 1.57079632;
	if (x > 3.14159265)
		x -= 6.28318531;
	if (x < 0)
		return 1.27323954 * x + 0.405284735 * x * x;
	else
		return 1.27323954 * x - 0.405284735 * x * x;
}

float EDPoint::getLength()
{
	return sqrt(x * x + y * y + z * z);
}

EDPoint* EDPoint::multiply(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return this;
}

EDPoint* EDPoint::divide(EDPoint* div)
{
	x /= div->x;
	y /= div->y;
	z /= div->z;
	return this;
}

EDPoint* EDPoint::sum(EDPoint* inc, float multiplier)
{
	x += inc->x * multiplier;
	y += inc->y * multiplier;
	z += inc->z * multiplier;
	return this;
}

EDPoint* EDPoint::sum(float inc)
{
	x += inc;
	y += inc;
	z += inc;
	return this;
}

EDPoint* EDPoint::subtract(EDPoint* decr)
{
	x -= decr->x;
	y -= decr->y;
	z -= decr->z;
	return this;
}

EDPoint* EDPoint::makeUnitary()
{
	float len = sqrt(x * x + y * y + z * z);
	if (len != 0.0f)
	{
		x /= len;
		y /= len;
		z /= len;
	}
	return this;
}

unsigned char EDPoint::getOctant()
{
	int bitmask = 
		(x >= 0 ? 1 + 8 + 16 + 128 : 2 + 4 + 32 + 64) &
		(y >= 0 ? 1 + 2 + 64 + 128 : 4 + 8 + 16 + 32) &
		(z >= 0 ? 1 + 2 + 4 + 8 : 16 + 32 + 64 + 128);
	switch (bitmask)
	{
	case 1: return 1;
	case 2: return 2;
	case 4: return 3;
	case 8: return 4;
	case 16: return 5;
	case 32: return 6;
	case 64: return 7;
	case 128: return 8;
	default: return 0;
	}
}

float EDPoint::dotProduct(EDPoint* b)
{
	// produto escalar, produto interno, dot product
	return x * b->x + y * b->y + z * b->z;
}

float EDPoint::angleTo(EDPoint* b)
{
	EDPoint na, nb;
	na.set(this)->makeUnitary();
	nb.set(b)->makeUnitary();
	return acos(DOTPRODUCT1(na, nb));
}

float EDPoint::signedAngle(EDPoint* u, EDPoint* v)
{
	EDPoint c;
	c.setCrossProduct(u, v);
	float angle = atan2(c.getLength(), DOTPRODUCT2(u, v));
	return DOTPRODUCT3(c, this) < 0.f ? -angle : angle;
}

float EDPoint::distanceTo(EDPoint* b)
{
	float dx = b->x - this->x;
	float dy = b->y - this->y;
	float dz = b->z - this->z;
	float dist = sqrt(dx * dx + dy * dy + dz * dz);
	return dist;
}

EDPoint* EDPoint::setCrossProduct(EDPoint* p1p2, EDPoint* p1p3)
{
	// produto vetorial, produto externo, cross product
	x = p1p2->y * p1p3->z - p1p2->z * p1p3->y;
	y = p1p2->z * p1p3->x - p1p2->x * p1p3->z;
	z = p1p2->x * p1p3->y - p1p2->y * p1p3->x;
	return this;
}

EDPoint* EDPoint::setVector(EDPoint* p1, EDPoint* p2)
{
	x = p2->x - p1->x;
	y = p2->y - p1->y;
	z = p2->z - p1->z;
	return this;
}

EDPoint* EDPoint::setCrossProduct(EDPoint* p1, EDPoint* p2, EDPoint* p3)
{
	EDPoint p1p2, p1p3;
	p1p2.setVector(p1, p2);
	p1p3.setVector(p1, p3);
	setCrossProduct(&p1p2, &p1p3);
	return this;
}

EDPoint* EDPoint::setIntersection(EDPlane* pl1, EDPlane* pl2, EDPlane* pl3)
{
	// TODO nunca foi testado
	/*
	http://paulbourke.net/geometry/3planes/
		d1 ( N2 * N3 ) + d2 ( N3 * N1 ) + d3 ( N1 * N2 )
P =	 -------------------------------------------------------------------------
 		N1 . ( N2 * N3 )
		*/
	EDPoint n23, n31, n12;
	n23.setCrossProduct(&pl2->normal, &pl3->normal)->multiply(pl1->d);
	n31.setCrossProduct(&pl3->normal, &pl1->normal)->multiply(pl2->d);
	n12.setCrossProduct(&pl1->normal, &pl2->normal)->multiply(pl3->d);
	this->set(&n23)->sum(&n31)->sum(&n12)->multiply(1.f / DOTPRODUCT1(pl1->normal, n23));
	return this;
}

void EDPoint::print(void)
{
	//printf("P: %f %f %f\n", x, y, z);
}

// EDBBox

void EDBBox::getSize(EDPoint* dest)
{
	dest->set(&upper);
	dest->subtract(&lower);
}

void EDBBox::toArray(float* dest)
{
	dest[0] = lower.x;
	dest[1] = lower.y;
	dest[2] = lower.z;
	dest[3] = upper.x;
	dest[4] = upper.y;
	dest[5] = upper.z;
}

EDBBox* EDBBox::fromArray(float* src)
{
	lower.x = src[0];
	lower.y = src[1];
	lower.z = src[2];
	upper.x = src[3];
	upper.y = src[4];
	upper.z = src[5];
	return this;
}

EDBBox* EDBBox::set(float x0, float y0, float z0, float x1, float y1, float z1)
{
	lower.x = x0;
	lower.y = y0;
	lower.z = z0;
	upper.x = x1;
	upper.y = y1;
	upper.z = z1;
	return this;
}

EDBBox* EDBBox::fromRect(EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d)
{
	lower.x = MIN(a->x, MIN(b->x, MIN(c->x, d->x)));
	lower.y = MIN(a->y, MIN(b->y, MIN(c->y, d->y)));
	lower.z = MIN(a->z, MIN(b->z, MIN(c->z, d->z)));
	upper.x = MAX(a->x, MAX(b->x, MAX(c->x, d->x)));
	upper.y = MAX(a->y, MAX(b->y, MAX(c->y, d->y)));
	upper.z = MAX(a->z, MAX(b->z, MAX(c->z, d->z)));
	return this;
}

void EDBBox::getRect(int side, EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d)
{
	switch (side)
	{
	case SIDE_TOP: a->set(lower.x, upper.y, lower.z); b->set(lower.x, upper.y, upper.z); c->set(upper.x, upper.y, upper.z); d->set(upper.x, upper.y, lower.z); break;
	case SIDE_BOTTOM: a->set(lower.x, lower.y, upper.z); b->set(lower.x, lower.y, lower.z); c->set(upper.x, lower.y, lower.z); d->set(upper.x, lower.y, upper.z); break;
	case SIDE_LEFT: a->set(lower.x, upper.y, upper.z); b->set(lower.x, upper.y, lower.z); c->set(lower.x, lower.y, lower.z); d->set(lower.x, lower.y, upper.z); break;
	case SIDE_RIGHT: a->set(upper.x, lower.y, upper.z); b->set(upper.x, lower.y, lower.z); c->set(upper.x, upper.y, lower.z); d->set(upper.x, upper.y, upper.z); break;
	case SIDE_FRONT: a->set(lower.x, lower.y, upper.z); b->set(upper.x, lower.y, upper.z); c->set(upper.x, upper.y, lower.z); d->set(lower.x, upper.y, lower.z); break;
	case SIDE_BACK: a->set(upper.x, lower.y, lower.z); b->set(lower.x, lower.y, lower.z); c->set(lower.x, upper.y, lower.z); d->set(upper.x, upper.y, lower.z); break;
	}
}

void EDBBox::toSphere(EDSphere* dest)
{
	float xrad = 0.5f * (upper.x - lower.x);
	float yrad = 0.5f * (upper.y - lower.y);
	float zrad = 0.5f * (upper.z - lower.z);
	float xx = xrad * xrad;
	float yy = yrad * yrad;
	float zz = zrad * zrad;
	float maxsq = xx;
	if (yy > maxsq)
		maxsq = yy;
	if (zz > maxsq)
		maxsq = zz;
	dest->radius = sqrt(2 * maxsq);
	dest->center.x = lower.x + xrad;
	dest->center.y = lower.y + yrad;
	dest->center.z = lower.z + zrad;
}

void EDBBox::toBSphere(EDSphere* dest)
{
	float halfwidth = 0.5f * (upper.x - lower.x);
	float halfheight = 0.5f * (upper.y - lower.y);
	float halfdeep = 0.5f * (upper.z - lower.z);
	float maxhalf = halfwidth;
	if (halfheight > maxhalf)
		maxhalf = halfheight;
	if (halfdeep > maxhalf)
		maxhalf = halfdeep;
	dest->radius = sqrt(3 * maxhalf * maxhalf);
	dest->center.x = lower.x + halfwidth;
	dest->center.y = lower.y + halfheight;
	dest->center.z = lower.z + halfdeep;
}

void EDBBox::getCenter(EDPoint* dest)
{
	dest->x = (upper.x + lower.x) / 2.0f;
	dest->y = (upper.y + lower.y) / 2.0f;
	dest->z = (upper.z + lower.z) / 2.0f;
}

bool EDBBox::intersects(EDBBox *b)
{
	return this->upper.x >= b->lower.x && this->upper.y >= b->lower.y && this->upper.z >= b->lower.z && 
		this->lower.x <= b->upper.x && this->lower.y <= b->upper.y && this->lower.z <= b->upper.z;
}


// EDTriangle

EDTriangle::EDTriangle(void)
{ }

EDTriangle::EDTriangle(EDPoint p1, EDPoint p2, EDPoint p3)
{
	this->p1 = EDPoint(p1.x, p1.y, p1.z);
	this->p2 = EDPoint(p2.x, p2.y, p2.z);
	this->p3 = EDPoint(p3.x, p3.y, p3.z);
}

EDTriangle::EDTriangle(EDTriangle* another)
{
	this->p1 = EDPoint(another->p1.x, another->p1.y, another->p1.z);
	this->p2 = EDPoint(another->p2.x, another->p2.y, another->p2.z);
	this->p3 = EDPoint(another->p3.x, another->p3.y, another->p3.z);
}

EDTriangle::~EDTriangle(void)
{ }

void EDTriangle::getNormal(EDPoint* dest)
{
	dest->setCrossProduct(&p1, &p2, &p3)->makeUnitary();
}

EDPoint EDTriangle::getNormal(void)
{
	EDPoint normal = EDPoint(0,0,0);
	normal.setCrossProduct(&p1, &p2, &p3);
	normal.makeUnitary();
	return normal;
}

void EDTriangle::translate(EDPoint toPoint)
{
	p1.x += toPoint.x;
	p1.y += toPoint.y;
	p1.z += toPoint.z;

	p2.x += toPoint.x;
	p2.y += toPoint.y;
	p2.z += toPoint.z;

	p3.x += toPoint.x;
	p3.y += toPoint.y;
	p3.z += toPoint.z;
}

void EDTriangle::rotate(EDPoint axis, EDPoint min, float angle)
{
	angle = angle*pi180;

	float cosa = cos(angle);
	float sina = sin(angle);

	translate(EDPoint(-1*min.x, -1*min.y, -1*min.z));

#pragma region rotation
	float xx = 0, yx = 0, zx = 0;

	EDPoint points[3];
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;

	xx = p1.x;
	yx = p1.y;
	zx = p1.z;

	if(axis.x != 0)
	{
		p1.y = cosa*yx - sina*zx;
		p1.z = sina*yx + cosa*zx;
	}
	if(axis.y != 0)
	{
		p1.x = cosa*xx + sina*zx;
		p1.z = -sina*xx + cosa*zx;
	}
	if(axis.z != 0)
	{
		p1.x = cosa*xx - sina*yx;
		p1.y = sina*xx + cosa*yx;
	}

	xx = p2.x;
	yx = p2.y;
	zx = p2.z;

	if(axis.x != 0)
	{
		p2.y = cosa*yx - sina*zx;
		p2.z = sina*yx + cosa*zx;
	}
	if(axis.y != 0)
	{
		p2.x = cosa*xx + sina*zx;
		p2.z = -sina*xx + cosa*zx;
	}
	if(axis.z != 0)
	{
		p2.x = cosa*xx - sina*yx;
		p2.y = sina*xx + cosa*yx;
	}

	xx = p3.x;
	yx = p3.y;
	zx = p3.z;

	if(axis.x != 0)
	{
		p3.y = cosa*yx - sina*zx;
		p3.z = sina*yx + cosa*zx;
	}
	if(axis.y != 0)
	{
		p3.x = cosa*xx + sina*zx;
		p3.z = -sina*xx + cosa*zx;
	}
	if(axis.z != 0)
	{
		p3.x = cosa*xx - sina*yx;
		p3.y = sina*xx + cosa*yx;
	}
#pragma endregion

	translate(EDPoint(min.x, min.y, min.z));
}

void EDTriangle::scale(EDPoint axis, EDPoint min, float factor)
{
	translate(EDPoint(-1*min.x, -1*min.y, -1*min.z));

	for(int i = 0; i < 8; i++)
	{
		if(axis.x != 0)
		{
			p1.x *= factor;
			p2.x *= factor;
			p3.x *= factor;
		}
		if(axis.y != 0)
		{
			p1.y *= factor;
			p2.y *= factor;
			p3.y *= factor;
		}
		if(axis.z != 0)
		{
			p1.z *= factor;
			p2.z *= factor;
			p3.z *= factor;
		}
	}
	translate(EDPoint(min.x, min.y, min.z));
}

// EDPlane

EDPlane::EDPlane()
{
	normal.x = normal.y = normal.z = d = 0;		
}

bool EDPlane::intercepts(EDBBox* bbox)
{
	EDSphere sphere;
	bbox->toSphere(&sphere);
	return this->intercepts(&sphere);
}

bool EDPlane::intercepts(EDSphere* sphere)
{
	return compute(&sphere->center) < sphere->radius;
}

EDPlane* EDPlane::normalize()
{
	float len = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
	if (len != 0.0f)
	{
		normal.x /= len;
		normal.y /= len;
		normal.z /= len;
		d /= len;
	}
	return this;
}

EDPlane* EDPlane::set(EDPlane* sample)
{
	this->normal = sample->normal;
	this->d = sample->d;
	return this;
}

EDPlane* EDPlane::set(float a, float b, float c, float d)
{
	this->normal.x = a;
	this->normal.y = b;
	this->normal.z = c;
	this->d = d;
	return this;
}

float EDPlane::compute(EDPoint* pt)
{
	return normal.x * pt->x + normal.y * pt->y + normal.z * pt->z + d;
}

bool EDPlane::isPositive(EDPoint* pt)
{
	return compute(pt) >= 0;
}

void EDPlane::invert()
{
	normal.x *= -1.f;
	normal.y *= -1.f;
	normal.z *= -1.f;
}

EDPlane* EDPlane::fromPoints(EDPoint* p0, EDPoint* p1, EDPoint* p2)
{
	EDPoint u, v;
	u.setVector(p0, p1);
	v.setVector(p0, p2);
	normal.setCrossProduct(&u, &v)->makeUnitary();
	d = -(normal.x * p0->x + normal.y * p0->y + normal.z * p0->z);
	return this;
}

// EDFrustum

float EDFrustum::initialAngle = 0.f;

EDFrustum::EDFrustum()
{
	angle = initialAngle;
}

void EDFrustum::rotate()
{
	if(angle != 0)
	{
		this->rotate(angle);
	}
}

void EDFrustum::printCorners(void)
{
	int j = 0;
	printf("Corner: \n");
	while(j < 8)
	{
		printf("%f %f %f\n", corners[j].x, corners[j].y, corners[j].z);
		j++;
	}
}

EDPoint EDFrustum::getNearDirection(void)
{
	return planes[PLANE_NEAR].normal;
}

void EDFrustum::rotate(float angle)
{
	EDPoint* base = &apex;//&corners[FRUSTUM_FBL];
	float x = base->x;
	float z = base->z;

	float _x, _z;
	
	angle = angle*pi180;

	float cosa = cos(angle);
	float sina = sin(angle);

	int j = 0;
	while(j < 8)
	{
		corners[j].x -= x;
		corners[j].z -= z;

		_x = corners[j].x;
		_z = corners[j].z;

		corners[j].x = _x*cosa - _z*sina;
		corners[j].z = _x*sina + _z*cosa;

		corners[j].x += x;
		corners[j].z += z;

		j++;
	}

	EDPoint ftl, ftr, fbr, fbl, ntl, ntr, nbr, nbl;
	ftl = corners[FRUSTUM_FTL];
	ftr = corners[FRUSTUM_FTR];
	fbl = corners[FRUSTUM_FBL];
	fbr = corners[FRUSTUM_FBR];
	ntl = corners[FRUSTUM_NTL];
	ntr = corners[FRUSTUM_NTR];
	nbl = corners[FRUSTUM_NBL];
	nbr = corners[FRUSTUM_NBR];

	planes[PLANE_RIGHT].fromPoints(&ntr, &ftr, &fbr);
	planes[PLANE_LEFT].fromPoints(&nbl, &fbl, &ftl);
	planes[PLANE_BOTTOM].fromPoints(&nbr, &fbr, &fbl);
	planes[PLANE_TOP].fromPoints(&ntl, &ftl, &ftr);
	planes[PLANE_FAR].fromPoints(&ftr, &ftl, &fbl);
	planes[PLANE_NEAR].fromPoints(&ntl, &ntr, &nbr);

	direction = planes[PLANE_NEAR].normal;
}

EDFrustum* EDFrustum::makeZ(float nx, float ny, float nz, float nw, float nh, float fw, float fh, float fz)
{
	EDPoint ftl, ftr, fbr, fbl, ntl, ntr, nbr, nbl;
	nbl.set(nx - nw / 2.0f, ny - nh / 2.0f, nz);
	nbr.set(nx + nw / 2.0f, ny - nh / 2.0f, nz);
	ntr.set(nx + nw / 2.0f, ny + nh / 2.0f, nz);
	ntl.set(nx - nw / 2.0f, ny + nh / 2.0f, nz);
	fbl.set(nx - fw / 2.0f, ny - fh / 2.0f, fz);
	fbr.set(nx + fw / 2.0f, ny - fh / 2.0f, fz);
	ftr.set(nx + fw / 2.0f, ny + fh / 2.0f, fz);
	ftl.set(nx - fw / 2.0f, ny + fh / 2.0f, fz);
	planes[PLANE_RIGHT].fromPoints(&ntr, &ftr, &fbr);
	planes[PLANE_LEFT].fromPoints(&nbl, &fbl, &ftl);
	planes[PLANE_BOTTOM].fromPoints(&nbr, &fbr, &fbl);
	planes[PLANE_TOP].fromPoints(&ntl, &ftl, &ftr);
	planes[PLANE_FAR].fromPoints(&ftr, &ftl, &fbl);
	planes[PLANE_NEAR].fromPoints(&ntl, &ntr, &nbr);
	corners[FRUSTUM_FTL] = ftl;
	corners[FRUSTUM_FTR] = ftr;
	corners[FRUSTUM_FBL] = fbl;
	corners[FRUSTUM_FBR] = fbr;
	corners[FRUSTUM_NTL] = ntl;
	corners[FRUSTUM_NTR] = ntr;
	corners[FRUSTUM_NBL] = nbl;
	corners[FRUSTUM_NBR] = nbr;
	apex.set(nx, ny, nz);
	return this;
}

EDFrustum* EDFrustum::makeFrustum(float fov, float aspect, float nearp, float farp, EDPoint apex)
{
	float angle = fov/2;
	angle = angle*PI/180.f;
	float nix = nearp*tan(angle);
	float nfx = farp*tan(angle);

	angle = aspect/2;
	angle = angle*PI/180.f;
	float niy = nearp*tan(angle);
	float nfy = farp*tan(angle);

	EDPoint ftl, ftr, fbr, fbl, ntl, ntr, nbr, nbl;
	ftl.set(apex.x - nfx, apex.y + nfy, apex.z - farp);
	ftr.set(apex.x + nfx, apex.y + nfy, apex.z - farp);
	fbl.set(apex.x - nfx, apex.y - nfy, apex.z - farp);
	fbr.set(apex.x + nfx, apex.y - nfy, apex.z - farp);
	
	ntl.set(apex.x - nix, apex.y + niy, apex.z - nearp);
	ntr.set(apex.x + nix, apex.y + niy, apex.z - nearp);
	nbl.set(apex.x - nix, apex.y - niy, apex.z - nearp);
	nbr.set(apex.x + nix, apex.y - niy, apex.z - nearp);

	planes[PLANE_RIGHT].fromPoints(&ntr, &ftr, &fbr);
	planes[PLANE_LEFT].fromPoints(&nbl, &fbl, &ftl);
	planes[PLANE_BOTTOM].fromPoints(&nbr, &fbr, &fbl);
	planes[PLANE_TOP].fromPoints(&ntl, &ftl, &ftr);
	planes[PLANE_FAR].fromPoints(&ftr, &ftl, &fbl);
	planes[PLANE_NEAR].fromPoints(&ntl, &ntr, &nbr);
	corners[FRUSTUM_FTL] = ftl;
	corners[FRUSTUM_FTR] = ftr;
	corners[FRUSTUM_FBL] = fbl;
	corners[FRUSTUM_FBR] = fbr;
	corners[FRUSTUM_NTL] = ntl;
	corners[FRUSTUM_NTR] = ntr;
	corners[FRUSTUM_NBL] = nbl;
	corners[FRUSTUM_NBR] = nbr;
	this->apex.set(apex.x, apex.y, apex.z);

	direction = planes[PLANE_NEAR].normal;

	return this;
}

bool EDFrustum::contains(float x, float y, float z)
{
	for (int i = 0; i < 6; ++i)
	{
		EDPlane* plane = &planes[i];
		// se o ponto estiver do lado negativo de algum dos 6 planos, ele esta fora do frustum
		float side = plane->normal.x * x + plane->normal.y * y + plane->normal.z * z + plane->d;
		if (side <= 0)
		{
			return false;
		}
	}
	return true;
}

bool EDFrustum::containsBounding(EDBBox* bounding)
{
	float x = bounding->lower.x;
	float y = bounding->lower.y;
	float z = bounding->lower.z;
	bool anyone = false;
	anyone |= contains(x,y,z);
	
	return anyone;
}

bool EDFrustum::contains(EDPoint* pt)
{
	return contains(pt->x, pt->y, pt->z);
}

bool EDFrustum::containsAnyVertexOf(EDBBox* bbox)
{
	// testa se pelo menos um dos vertices do cubo esta dentro do VF
	EDPoint* corners[2] = {&bbox->lower, &bbox->upper};
	int cx = 0, cy = 0, cz = 0;
	for (int i = 0; i < 8; i++)
	{
		//printf("%d %d %d\n",cx,cy,cz);
		if (contains(corners[cx]->x, corners[cy]->y, corners[cz]->z))
		{
			return true;
		}
		if (!(cz ^= 1))
		{
			if (!(cy ^= 1))
			{
				cx ^= 1;
			}
		}
	}
	return false;
}

bool EDFrustum::contains(EDBBox* bbox)
{
	return containsAllVertexOf(bbox);
}

bool EDFrustum::containsAllVertexOf(EDBBox* bbox)
{
	// testa se pelo menos um dos vertices do cubo esta dentro do VF
	EDPoint* corners[2] = {&bbox->lower, &bbox->upper};
	int cx = 0, cy = 0, cz = 0;
	for (int i = 0; i < 8; i++)
	{
		if (!contains(corners[cx]->x, corners[cy]->y, corners[cz]->z))
		{
			return false;
		}
		if (!(cz ^= 1))
		{
			if (!(cy ^= 1))
			{
				cx ^= 1;
			}
		}
	}
	return true;
}

bool EDFrustum::intercepts(EDTriangle* tri)
{
	// TODO caso especial
	return contains(&tri->p1) || contains(&tri->p2) || contains(&tri->p3);
}

bool EDFrustum::intercepts(EDBBox* bbox)
{
	// se nenhum vertice estiver dentro do frustum, pode ser o caso especial, no qual o frustum estah dentro do cubo
	// ai, eu projeto a bounding-sphere e testo a intersecao dela com o frustum
	bool found = containsAnyVertexOf(bbox);
	if (!found)
	{
		EDSphere sphere;
		bbox->toSphere(&sphere);
		found = intercepts(&sphere);
	}
	return found;
}

EDBBox EDFrustum::getBBox(void)
{
	EDBBox newBBox = EDBBox();
	EDPoint* minimum = new EDPoint( 999999999.f,  999999999.f, 999999999.f);
	EDPoint* maximum = new EDPoint(-999999999.f, -999999999.f,-999999999.f);
	
	int j = 0;
	while(j < 8)
	{
		if(minimum->x >= corners[j].x)
		{
			minimum->x = corners[j].x;
		}
		if(maximum->x <= corners[j].x)
		{
			maximum->x = corners[j].x;
		}
		if(minimum->y >= corners[j].y)
		{
			minimum->y = corners[j].y;
		}
		if(maximum->y <= corners[j].y)
		{
			maximum->y = corners[j].y;
		}
		if(minimum->z >= corners[j].z)
		{
			minimum->z = corners[j].z;
		}
		if(maximum->z <= corners[j].z)
		{
			maximum->z = corners[j].z;
		}
		j++;
	}

	newBBox.upper = *maximum;
	newBBox.lower = *minimum;

	delete minimum;
	delete maximum;

	return newBBox;
}

bool EDFrustum::testBBox(EDBBox* bbox)
{
	EDBBox* newBBox = &getBBox();
	//printf("%f %f %f\n", newBBox->lower.x, newBBox.lower.y, newBBox.lower.z);
	//return newBBox->upper.x >= bbox->lower.x && newBBox->upper.z >= bbox->lower.z;
	//return newBBox->lower.x <= bbox->upper.x && newBBox->lower.z <= bbox->upper.z;

	return newBBox->upper.x >= bbox->lower.x && newBBox->lower.x <= bbox->upper.x
	&& newBBox->upper.z >= bbox->lower.z && newBBox->lower.z <= bbox->upper.z;
}

bool EDFrustum::intercepts(EDSphere* sphere)
{
	for (int i = 0; i < 6; ++i)
	{
		EDPlane* plane = &planes[i];
		float dist = plane->normal.x * sphere->center.x + plane->normal.y * sphere->center.y + plane->normal.z * sphere->center.z + plane->d;
		if (dist <= -sphere->radius )
			return false;
	}
	return true;
}

void EDFrustum::computePlanes(float projection[16], float modelView[16])
{
	float* p = projection;
	float* mv = modelView;
	float mvp[16]; // Anotações do Ronaldo: Model-View-Projection Matrix

	//Anotações do Ronaldo: Concatenate the projection matrix and the model-view matrix to produce
	//a combined model-view-projection matrix.
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++){
				sum += mv[i * 4 + k] * p[k * 4 + j];
			}
			mvp[i * 4 + j] = sum;
		}
	}

	planes[PLANE_RIGHT].set(mvp[3] - mvp[0], mvp[7] - mvp[4], mvp[11] - mvp[8], mvp[15] - mvp[12]);
	planes[PLANE_LEFT].set(mvp[3] + mvp[0], mvp[7] + mvp[4], mvp[11] + mvp[8], mvp[15] + mvp[12]);
	planes[PLANE_BOTTOM].set(mvp[3] + mvp[1], mvp[7] + mvp[5], mvp[11] + mvp[9], mvp[15] + mvp[13]);
	planes[PLANE_TOP].set(mvp[3] - mvp[1], mvp[7] - mvp[5], mvp[11] - mvp[9], mvp[15] - mvp[13]);
	planes[PLANE_FAR].set(mvp[3] - mvp[2], mvp[7] - mvp[6], mvp[11] - mvp[10], mvp[15] - mvp[14]);
	planes[PLANE_NEAR].set(mvp[3] + mvp[2], mvp[7] + mvp[6], mvp[11] + mvp[10], mvp[15] + mvp[14]);

	for (int i = 0; i < 6; i++){
		planes[i].normalize();
	}
}

void EDFrustum::computeCorners()
{
	corners[FRUSTUM_NTL].setIntersection(&planes[PLANE_NEAR], &planes[PLANE_LEFT], &planes[PLANE_TOP]);
	corners[FRUSTUM_NTR].setIntersection(&planes[PLANE_NEAR], &planes[PLANE_TOP], &planes[PLANE_RIGHT]);
	corners[FRUSTUM_NBR].setIntersection(&planes[PLANE_NEAR], &planes[PLANE_RIGHT], &planes[PLANE_BOTTOM]);
	corners[FRUSTUM_NBL].setIntersection(&planes[PLANE_NEAR], &planes[PLANE_BOTTOM], &planes[PLANE_LEFT]);
	corners[FRUSTUM_FTL].setIntersection(&planes[PLANE_FAR], &planes[PLANE_LEFT], &planes[PLANE_TOP]);
	corners[FRUSTUM_FTR].setIntersection(&planes[PLANE_FAR], &planes[PLANE_TOP], &planes[PLANE_RIGHT]);
	corners[FRUSTUM_FBR].setIntersection(&planes[PLANE_FAR], &planes[PLANE_RIGHT], &planes[PLANE_BOTTOM]);
	corners[FRUSTUM_FBL].setIntersection(&planes[PLANE_FAR], &planes[PLANE_BOTTOM], &planes[PLANE_LEFT]);
}

void limitPt(EDPoint* a, EDPoint* b, EDBBox* limits)
{
	EDPoint v;
	v.setVector(a, b);
	if (b->x > limits->upper.x)
	{
		v.multiply((limits->upper.x - a->x) / v.x);
		b->set(a)->sum(&v);
	}
	if (b->y > limits->upper.y)
	{
		v.multiply((limits->upper.y - a->y) / v.y);
		b->set(a)->sum(&v);
	}
	if (b->z > limits->upper.z)
	{
		v.multiply((limits->upper.z - a->z) / v.z);
		b->set(a)->sum(&v);
	}
	if (b->x < limits->lower.x)
	{
		v.multiply((limits->lower.x - a->x) / v.x);
		b->set(a)->sum(&v);
	}
	if (b->y < limits->lower.y)
	{
		v.multiply((limits->lower.y - a->y) / v.y);
		b->set(a)->sum(&v);
	}
	if (b->z < limits->lower.z)
	{
		v.multiply((limits->lower.z - a->z) / v.z);
		b->set(a)->sum(&v);
	}
}

// EDShadow

EDShadow::EDShadow()
{
	angle = 0;
	tag = 0;
}

bool EDShadow::hides(EDTriangle* tri)
{
	return contains(&tri->p1) && contains(&tri->p2) && contains(&tri->p3);
}

bool EDShadow::contains(EDPoint* pt)
{
	return np.isPositive(pt) && tp.isPositive(pt) && rp.isPositive(pt) && bp.isPositive(pt) && lp.isPositive(pt);
}

bool EDShadow::contains(float x, float y, float z)
{
	EDPoint pt;
	pt.x = x;
	pt.y = y;
	pt.z = z;
	return contains(&pt);
}

bool EDShadow::contains(EDSphere* sphere)
{
	if (np.compute(&sphere->center) <= sphere->radius)
		return false;
	if (lp.compute(&sphere->center) <= sphere->radius)
		return false;
	if (rp.compute(&sphere->center) <= sphere->radius)
		return false;
	if (bp.compute(&sphere->center) <= sphere->radius)
		return false;
	if (tp.compute(&sphere->center) <= sphere->radius)
		return false;
	return true;
}

bool EDShadow::contains(EDBBox* box)
{
	if (containsAllVertexOf(box))
		return true;
	EDSphere sphere;
	box->toSphere(&sphere);
	return contains(&sphere);
}

bool EDShadow::containsAllVertexOf(EDBBox* box)
{
	// testa se pelo menos um dos vertices do cubo esta dentro do VF
	EDPoint* corners[2] = {&box->lower, &box->upper};
	int cx = 0, cy = 0, cz = 0;
	for (int i = 0; i < 8; i++)
	{
		if (!contains(corners[cx]->x, corners[cy]->y, corners[cz]->z))
			return false;
		if (!(cz ^= 1))
			if (!(cy ^= 1))
				cx ^= 1;
	}
	return true;
}

void makeFar(EDPoint* dest, EDPoint* apex, EDPoint* nearPoint, float len)
{
	dest->setVector(apex, nearPoint)->makeUnitary()->multiply(len)->sum(nearPoint, 1.0f);
}

void EDShadow::computeFar(float len)
{
	// o plano far eh formado pela projecao dos pontos do plano near pelo apex, o comprimento eh indicado pelo usuario
	// obs: na sombra eu nao preciso do plano far, ou ele eh infinito, essa funcao eh soh pra poder desenhar a sombra
	makeFar(&ftl, &apex, &ntl, len);
	makeFar(&ftr, &apex, &ntr, len);
	makeFar(&fbr, &apex, &nbr, len);
	makeFar(&fbl, &apex, &nbl, len);
}

EDShadow* EDShadow::fromApex(EDPoint* apex, EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d)
{
	// vou corrigir as coordenadas, obtendo no final, tl,tr,br e bl
	// mid eh o meio do plano near, up eh esse meio mais pra cima
	EDPoint mid, up;
	mid.x = (a->x + b->x + c->x + d->x) / 4.0f;
	mid.y = (a->y + b->y + c->y + d->y) / 4.0f;
	mid.z = (a->z + b->z + c->z + d->z) / 4.0f;
	up.set(mid.x, mid.y + 1.0f, mid.z);

	// com apex,mid,up nessa ordem, eu obtenho um plano q me diz quais pts estao a direita da linha do olhar
	EDPlane pl;
	pl.fromPoints(apex, &mid, &up);

	// vou classificar quais pts estao a direita e quais estao a esquerda, devem ser 2 pra cada lado, senao, o plano abcd nao eh valido para esse apex
	EDPoint* l[4];
	EDPoint* r[4];
	int lc = 0;
	int rc = 0;
	if (pl.isPositive(a))
		r[rc++] = a;
	else
		l[lc++] = a;
	if (pl.isPositive(b))
		r[rc++] = b;
	else
		l[lc++] = b;
	if (pl.isPositive(c))
		r[rc++] = c;
	else
		l[lc++] = c;
	if (pl.isPositive(d))
		r[rc++] = d;
	else
		l[lc++] = d;
	if (lc != 2 || rc != 2)
		return NULL;

	// agora q eu sei os pontos q estao a direita, eu vou dizer quem esta acima apenas comparando o Y (o mesmo pros da esquerda)
	if (l[0]->y > l[1]->y)
	{
		ntl = *l[0];
		nbl = *l[1];
	}
	else
	{
		ntl = *l[1];
		nbl = *l[0];
	}
	if (r[0]->y > r[1]->y)
	{
		ntr = *r[0];
		nbr = *r[1];
	}
	else
	{
		ntr = *r[1];
		nbr = *r[0];
	}

	// blz, eh soh criar os planos da shadow agora
	this->apex = *apex;
	this->np.fromPoints(&ntl, &ntr, &nbr);
	this->bp.fromPoints(apex, &nbr, &nbl);
	this->lp.fromPoints(apex, &nbl, &ntl);
	this->rp.fromPoints(apex, &ntr, &nbr);
	this->tp.fromPoints(apex, &ntl, &ntr);

	// aproveito a carona e calculo o solid-angle (minha versao)
	float hangle = PI - lp.normal.angleTo(&rp.normal);
	float vangle = PI - tp.normal.angleTo(&bp.normal);
	this->angle = MAX(hangle, vangle);

	return this;
}

// EDSphere

bool EDSphere::contains(EDPoint* pt)
{
	float dist = pt->distanceTo(&center);
	return !(dist > radius);
}

// EDUmbra

EDUmbra::EDUmbra()
{
	areaAngle = 0;
	next = NULL;
	enabled = false;
	valid = false;
	tag = 0;
}

void swapPtRefs(EDPoint* &a, EDPoint* &b)
{
	EDPoint* aux = a;
	a = b;
	b = aux;
}

void swapPtVars(EDPoint &a, EDPoint &b)
{
	EDPoint aux = a;
	a = b;
	b = aux;
}

EDUmbra* EDUmbra::makeZ(float apexx, float apexy, float apexz, float fw, float fh, float fz)
{
	EDPoint apex, a, b, c, d, mp, look;
	apex.set(apexx, apexy, apexz);
	a.set(apexx - fw / 2.0f, apexy - fh / 2.0f, fz);
	b.set(apexx - fw / 2.0f, apexy + fh / 2.0f, fz);
	c.set(apexx + fw / 2.0f, apexy + fh / 2.0f, fz);
	d.set(apexx + fw / 2.0f, apexy - fh / 2.0f, fz);
	mp.setMiddle(&a, &c);
	look.setVector(&apex, &mp);
	return fromOccluder(&apex, &look, &a, &b, &c, &d);
}

float classifyPoligon(EDPoint* middle, EDPoint* normal, EDPoint* camdir, EDPoint* campos)
{
	EDPoint n, v, d, p;

	// Apresentado por Coorg'97
	// g = -a*dot(n,v)/dot(d,d)
	// a = area of the occluder
	// n = normal
	// v = view direction
	// d = vector from viewpoint to occluder	
	n = *normal; ///TODO usar ptr
	v = *camdir;
	p = *campos;
	float x = middle->x;
	float y = middle->y;
	float z = middle->z;
	d.set(x - p.x, y - p.y, z - p.z)->makeUnitary();
	float a = n.x * n.x + n.y * n.y + n.z * n.z;
	float nv = n.dotProduct(&v);
	float dd = d.dotProduct(&d);
	float g = a * nv / dd;
	return g;
}

EDUmbra* EDUmbra::fromOccluder(EDPoint* eye, EDPoint* dir, EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d)
{
	// pego dois pontos arbitrariamente (A e B), para os quais ha duas possibilidades: A e B estao do mesmo lado do 
	// retangulo (C e D ficam do outro lado), ou A e B sao vertices opostos (C e D sao os outros vertices)
	// formo um plano com A, B e EYE (jah posso dizer se alguem estah a direita ou esquerda desse plano)
	// verifico se C e D estao do mesmo lado do plano ou em lados opostos; sabendo isso, resta deixar os pontos ordenados em sentido ANTI-HORARIO!!!
	// se ladoAB e ladoCD: formo um plano com [EYE, meioAB e meioCD]
	EDPlane pl;
	pl.fromPoints(eye, a, b);
	float csig = pl.compute(c);
	float dsig = pl.compute(d);
	if (csig > 0 && dsig > 0)
	{
		// AB de um lado, CD do outro positivo em relacao ao plano [eye,a,b]
		// crio pontos intermediarios entre A-B e entre C-D, e formo plano com esse intermediarios e o EYE
		// nesse plano: A tem q ficar do mesmo lado q D, e B do lado de C
		EDPoint ab, cd;
		ab.setMiddle(a, b);
		cd.setMiddle(c, d);
		pl.fromPoints(eye, &cd, &ab);
		float asig = pl.compute(a);
		if (asig < 0)
			swapPtRefs(a, b);
		csig = pl.compute(c);
		if (csig > 0)
			swapPtRefs(c, d);
	}
	else if (csig < 0 && dsig < 0)
	{
		EDPoint ab, cd;
		ab.setMiddle(a, b);
		cd.setMiddle(c, d);
		pl.fromPoints(eye, &ab, &cd);
		float asig = pl.compute(a);
		if (asig > 0)
			swapPtRefs(a, b);
		csig = pl.compute(c);
		if (csig < 0)
			swapPtRefs(c, d);
	}
	else if (csig > 0 && dsig < 0)
	{
		pl.fromPoints(eye, c, d);
		float asig = pl.compute(a);
		if (asig > 0)
			swapPtRefs(a, d);
		else if (asig < 0)
		{
			swapPtRefs(a, d);
			swapPtRefs(b, d);
		}
		else
			return NULL;
	}
	else if (csig < 0 && dsig > 0)
	{
		pl.fromPoints(eye, c, d);
		float asig = pl.compute(a);
		if (asig > 0)
		{
			swapPtRefs(a, c);
			swapPtRefs(c, d);
		}
		else if (asig < 0)
			swapPtRefs(a, d);
		else
			return NULL;
	}
	else
		return NULL;

	apex = *eye;
	nearpt[0] = *a;
	nearpt[1] = *b;
	nearpt[2] = *c;
	nearpt[3] = *d;

	planes[PLANE_NEAR].fromPoints(c, b, a); //near
	planes[PLANE_LEFT].fromPoints(eye, b, a); // left
	planes[PLANE_BOTTOM].fromPoints(eye, c, b); // bottom
	planes[PLANE_RIGHT].fromPoints(eye, d, c); // right
	planes[PLANE_TOP].fromPoints(eye, a, d); // top

	// area angle piramide (http://en.wikipedia.org/wiki/Solid_angle)
	EDPoint va; va.setVector(eye, a);
	EDPoint vb; vb.setVector(eye, b);
	EDPoint vc; vc.setVector(eye, c);
	EDPoint vd; vd.setVector(eye, d);
	float angac = va.angleTo(&vc);
	float angbd = vb.angleTo(&vd);
	areaAngle = 4.f * asin(sin(angac / 2.f) * sin(angbd / 2.f));
	return this;
}

bool EDUmbra::contains(EDPoint* pt)
{
	for (int i = 0; i < 5; i++)
		if (planes[i].compute(pt) < 0)
			return false;
	return true;
}

bool EDUmbra::contains(EDBBox* box)
{
	EDSphere s;
	box->toSphere(&s);
	return contains(&s);
}

bool EDUmbra::contains(EDSphere* sphere)
{
	for (int i = 0; i < 5; i++)
		if (planes[i].compute(&sphere->center) < sphere->radius)
			return false;
	return true;
}
