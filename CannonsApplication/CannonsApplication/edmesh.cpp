#include "edmesh.h"

#include "edobjreader.h"

//#define drawArrays
#define max_value +2.0e-20

EDMesh::EDMesh(const char* identifier) :  GObject(identifier)
{ }

EDMesh::EDMesh(const char* identifier, char* path, char* filename) : GObject(identifier)
{
	EDObjReader reader = EDObjReader(path, filename);
	trianglesCount = reader.trianglesSize;
	triangles = new EDTriangle[trianglesCount];
	normals = new float[trianglesCount / 3];

	int k = 0;

#pragma region setando valores das normais e dos vértices; carregando valor mínimo
	for(int i = 0; i < reader.trianglesSize; i++)
	{
		EDTriangle triangle = reader.triangles[i];
		triangles[i] = EDTriangle(triangle.p1, triangle.p2, triangle.p3);

		EDPoint normal = EDPoint(0,0,0);
		triangle.getNormal(&normal);
		normals[k++] = normal.x;
		normals[k++] = normal.y;
		normals[k++] = normal.z;

	}
#pragma endregion
}

EDMesh::~EDMesh(void)
{
	if(triangles)
		delete[] triangles;
	if(normals)
		delete[] normals;
}

void EDMesh::calculateNormals(void)
{

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
		glVertex3f(triangles[i].p1.x, triangles[i].p1.y, triangles[i].p1.z);
		glVertex3f(triangles[i].p2.x, triangles[i].p2.y, triangles[i].p2.z);
		glVertex3f(triangles[i].p3.x, triangles[i].p3.y, triangles[i].p3.z);
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

void EDMesh::translate(EDPoint toPoint)
{
	for(int i = 0; i < trianglesCount;)
	{
		/*triangles[i++] += toPoint.x;
		triangles[i++] += toPoint.y;
		triangles[i++] += toPoint.z;*/
	}
}