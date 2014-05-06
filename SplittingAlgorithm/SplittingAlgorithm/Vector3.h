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

	void normalize(void);
	void printConsole(void);
	float magnitude(void);
	float dotProduct(Vector3 another);
	bool equals(Vector3 another);
	Vector3 subtract(Vector3 another);
	Vector3 crossProduct(Vector3 another);

	static Vector3 randomColor(void);
};

#endif