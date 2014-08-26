#include "edmesh.h"

#include "edobjreader.h"

#define drawArrays
#define max_value +2.0e-20

EDMesh::EDMesh(const char* identifier) :  GObject(identifier)
{ }

EDMesh::EDMesh(const char* identifier, char* path, char* filename) : GObject(identifier)
{
	EDObjReader reader = EDObjReader(path, filename);
	trianglesCount = reader.trianglesSize * 9;
	triangles = new float[trianglesCount];
	normals = new float[trianglesCount / 3];

	min = EDPoint(max_value,max_value,max_value);

	int j = 0;
	int k = 0;

#pragma region setando valores das normais e dos vértices; carregando valor mínimo
	for(int i = 0; i < reader.trianglesSize; i++)
	{
		EDTriangle triangle = reader.triangles[i];
		triangles[j++] = triangle.p1.x;
		if(triangles[j-1] < min.x)
		{
			min.x = triangles[j-1];
		}
		triangles[j++] = triangle.p1.y;
		if(triangles[j-1] < min.y)
		{
			min.y = triangles[j-1];
		}
		triangles[j++] = triangle.p1.z;
		if(triangles[j-1] < min.z)
		{
			min.z = triangles[j-1];
		}
		triangles[j++] = triangle.p2.x;
		if(triangles[j-1] < min.x)
		{
			min.x = triangles[j-1];
		}
		triangles[j++] = triangle.p2.y;
		if(triangles[j-1] < min.y)
		{
			min.y = triangles[j-1];
		}
		triangles[j++] = triangle.p2.z;
		if(triangles[j-1] < min.z)
		{
			min.z = triangles[j-1];
		}
		triangles[j++] = triangle.p3.x;
		if(triangles[j-1] < min.x)
		{
			min.x = triangles[j-1];
		}
		triangles[j++] = triangle.p3.y;
		if(triangles[j-1] < min.y)
		{
			min.y = triangles[j-1];
		}
		triangles[j++] = triangle.p3.z;
		if(triangles[j-1] < min.z)
		{
			min.z = triangles[j-1];
		}
		EDPoint normal = EDPoint(0,0,0);
		triangle.getNormal(&normal);
		normals[k++] = normal.x;
		normals[k++] = normal.y;
		normals[k++] = normal.z;

	}
#pragma endregion
	min.print();
}

EDMesh::~EDMesh(void)
{
	if(triangles)
		delete[] triangles;
	if(normals)
		delete[] normals;
}

void EDMesh::draw(void)
{ 
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuseMaterial);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 90.0f);

#ifdef drawArrays
	glVertexPointer(3, GL_FLOAT, 0, triangles);
	glNormalPointer(GL_FLOAT, 0, normals);
	glDrawArrays(GL_TRIANGLES, 0, trianglesCount/3);
#else
	glBegin(GL_TRIANGLES);
	int j = 0;
	for(int i = 0; i < trianglesCount;)
	{
		glNormal3f(normals[j++], normals[j++], normals[j++]);
		glVertex3f(triangles[i++], triangles[i++], triangles[i++]);
		glVertex3f(triangles[i++], triangles[i++], triangles[i++]);
		glVertex3f(triangles[i++], triangles[i++], triangles[i++]);
	}
	glEnd();
#endif
}

void EDMesh::update(float elapsedTime)
{ }

void EDMesh::setMaterial(GLfloat* ambient, GLfloat* diffuse)
{
	for(int i = 0; i < 4; i++)
	{
		ambientMaterial[i] = ambient[i];
		diffuseMaterial[i] = diffuse[i];
	}
}