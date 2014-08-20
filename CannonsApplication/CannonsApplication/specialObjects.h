#ifndef __SPECIAL_OBJECTS__
#define __SPECIAL_OBJECTS__

#include "geometricObjects.h"

class CannonBall : public GObject
{
public:
	float size;
	int length;
	EDPoint* targets;
private:
	int index;
	EDPoint* actualPosition;
	GCube* cube;
public:
	CannonBall(const char* identifier);
	CannonBall(const char* identifier, EDPoint* targets, int length, float size);
	~CannonBall(void);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);
private:
	void initialize(EDPoint* targets, int length, float size);
};

class KickingBall : public GObject
{
public:
	float size;
	float force;
	float mass;
	float velocity;
	float initialVelocity;
private:
	int index;
	GCube* cube;
public:
	KickingBall(const char* identifier);
	KickingBall(const char* identifier, GCube* cube, float velocity);
	~KickingBall(void);

	void draw(void);
	void update(float elapsedTime);

	void setMaterial(GLfloat* ambient, GLfloat* diffuse);
private:
	void initialize(GCube* cube, float velocity);
	void updateParams(void);
};

#endif
