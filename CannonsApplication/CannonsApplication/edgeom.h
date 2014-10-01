#ifndef __ED_GEOM__
#define __ED_GEOM__

#include <windows.h>
#include <GL/gl.h>
#include <math.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define BYTE unsigned char

#define DOTPRODUCT1(u,v) (u.x * v.x + u.y * v.y + u.z * v.z)
#define DOTPRODUCT2(pu,pv) (pu->x * pv->x + pu->y * pv->y + pu->z * pv->z)
#define DOTPRODUCT3(u,pv) (u.x * pv->x + u.y * pv->y + u.z * pv->z)

#define UNSAFEANGLE1(u,v) acos(DOTPRODUCT1(u,v))
#define UNSAFEANGLE3(u,pv) acos(DOTPRODUCT3(u,pv))

#undef PI
#define PI (3.1415926535897932384626433832795f)
#define pi180 3.14159265359/180.f

class EDPlane;

class EDPoint
{
public:
	float x, y, z;
public:
	EDPoint(void);
	EDPoint(float x, float y, float z);
	~EDPoint(void);
	EDPoint* set(float x, float y, float z);
	EDPoint* set(EDPoint* from);
	float getLength();
	unsigned char getOctant();
	float dotProduct(EDPoint* b);
	float angleTo(EDPoint* b);
	float distanceTo(EDPoint* b);
	EDPoint* setMiddle(EDPoint* a, EDPoint* b);
	EDPoint* setCrossProduct(EDPoint* p1p2, EDPoint* p1p3);
	EDPoint* setCrossProduct(EDPoint* p1, EDPoint* p2, EDPoint* p3);
	EDPoint* setVector(EDPoint* p1, EDPoint* p2);
	EDPoint* makeUnitary();
	EDPoint* multiply(float f);
	EDPoint* divide(EDPoint* div);
	EDPoint* sum(EDPoint* incr, float multiplier = 1.0f);
	EDPoint* sum(float inc);
	EDPoint* subtract(EDPoint* decr);
	EDPoint* setIntersection(EDPlane* pl1, EDPlane* pl2, EDPlane* pl3);

	void rotateAccordingTo(EDPoint* pivot, EDPoint axis, float angle);
	
	float isMultiple(EDPoint* v);
	float signedAngle(EDPoint* u, EDPoint* v);
	bool equals(EDPoint* b);
	bool almostEquals(float p);
	bool almostEquals(EDPoint* b);
	bool almostEquals(EDPoint* b, float precision);
	void print(void);
	void toVertex3f(void);
};

class EDSphere
{
public:
	EDPoint center;
	float radius;
	bool contains(EDPoint* pt);
};

const int SIDE_TOP = 0;
const int SIDE_BOTTOM = 1;
const int SIDE_LEFT = 2;
const int SIDE_RIGHT = 3;
const int SIDE_FRONT = 4;
const int SIDE_BACK = 5;

class EDBBox
{
public:
	EDPoint lower, upper;
public:
	void toArray(float* dest);
	void toSphere(EDSphere* dest);
	void toBSphere(EDSphere* dest);
	void getCenter(EDPoint* dest);
	void getRect(int side, EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d);
	EDBBox* fromArray(float* src);
	EDBBox* fromRect(EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d);
	EDBBox* set(float x0, float y0, float z0, float x1, float y1, float z1);
	void getSize(EDPoint* dest);
	bool intersects(EDBBox *b);
};

class EDTriangle
{
public:
	EDPoint p1, p2, p3;
public:
	EDTriangle(void);
	EDTriangle(EDTriangle* another);
	EDTriangle(EDPoint p1, EDPoint p2, EDPoint p3);
	~EDTriangle(void);
	void getNormal(EDPoint* dest);
	EDPoint getNormal(void);
	
	void translate(EDPoint toPoint);
	void rotate(EDPoint axis, EDPoint min, float angle);
	void scale(EDPoint axis, EDPoint min, float factor);
};

class EDPlane
{
public:
	EDPoint normal;
	float d;
public:
	EDPlane();
	bool isPositive(EDPoint* pt);
	bool intercepts(EDBBox* bbox);
	bool intercepts(EDSphere* sphere);
	EDPlane* normalize();
	EDPlane* set(float a, float b, float c, float d);
	EDPlane* set(EDPlane* sample);
	float compute(EDPoint* pt);
	EDPlane* fromPoints(EDPoint* p0, EDPoint* p1, EDPoint* p2);
	void invert();
};

#define FRUSTUM_FTL 0
#define FRUSTUM_FTR 1
#define FRUSTUM_FBL 2
#define FRUSTUM_FBR 3
#define FRUSTUM_NTL 4
#define FRUSTUM_NTR 5
#define FRUSTUM_NBL 6
#define FRUSTUM_NBR 7

#define PLANE_NEAR 0
#define PLANE_LEFT 1
#define PLANE_TOP 2
#define PLANE_RIGHT 3
#define PLANE_BOTTOM 4
#define PLANE_FAR 5

class EDFrustum
{
public:
	static float initialAngle;
	float angle;

	EDPlane planes[6];
	EDPoint corners[8];
	EDPoint apex;
	EDPoint direction;
public:
	EDFrustum();

	bool intercepts(EDTriangle* tri);
	bool intercepts(EDBBox* bbox);
	bool intercepts(EDSphere* sphere);
	bool testBBox(EDBBox* bbox);
	bool contains(float x, float y, float z);
	bool contains(EDPoint* pt);
	bool contains(EDBBox* bbox);
	bool containsBounding(EDBBox* bounding);
	bool containsAnyVertexOf(EDBBox* bbox);
	bool containsAllVertexOf(EDBBox* bbox);
	void computePlanes(float projection[16], float modelView[16]);
	void computeCorners();
	void computeBBox(EDBBox &dest, EDBBox* limits);
	void rotate();
	void rotate(float angle);
	void printCorners(void);
	EDBBox getBBox(void);
	EDPoint getNearDirection(void);
	EDFrustum* makeZ(float nx, float ny, float nz, float nw, float nh, float fw, float fh, float fz);
	EDFrustum* makeFrustum(float fov, float aspect, float nearp, float farp, EDPoint apex);
};

class EDShadow
{
private:
	bool containsAllVertexOf(EDBBox* bbox);
public:
	EDShadow();
	EDPlane np, tp, rp, bp, lp;

	EDPoint apex,nbr,nbl,ntl,ntr,fbr,fbl,ftl,ftr;///
	float angle;
	EDShadow* next;
	int tag;///

	bool hides(EDTriangle* tri);
	bool contains(float x, float y, float z);
	bool contains(EDPoint* pt);
	bool contains(EDBBox* box);
	bool contains(EDSphere* sphere);
	EDShadow* fromApex(EDPoint* apex, EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d);
	void computeFar(float len);
};

class EDUmbra
{
public:
	EDUmbra();
	EDPlane planes[5];
	float areaAngle;
	EDUmbra* next;
	bool enabled, valid;
	int index;
	int tag;
	EDPoint apex, nearpt[4];
public:
	EDUmbra* fromOccluder(EDPoint* eye, EDPoint* look, EDPoint* a, EDPoint* b, EDPoint* c, EDPoint* d);
	EDUmbra* makeZ(float apexx, float apexy, float apexz, float fw, float fh, float fz);
	bool contains(EDPoint* pt);
	bool contains(EDBBox* box);
	bool contains(EDSphere* sphere);
	void computeFar(float len);
	void computeAreaAngle(EDPoint* pos, EDPoint* dir);
	void computeBBox(EDBBox &dest, EDBBox* limits);
};

void swapPtRefs(EDPoint* &a, EDPoint* &b);
void swapPtVars(EDPoint &a, EDPoint &b);
void limitPt(EDPoint* a, EDPoint* b, EDBBox* limits);

float fastSqrt(const float x);
float fastACos(float x);
float fastSin(float x);
float fastCos(float x);

int getCurrentMS();

#endif