#ifndef __VECTOR_3__
#define __VECTOR_3__

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3(void);
	Vector3(float x, float y);
	Vector3(float x, float y, float z);
	Vector3(Vector3* copy);

	void printConsole(void);
	float dotProduct(Vector3 another);
};

#endif