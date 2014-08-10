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

#endif
