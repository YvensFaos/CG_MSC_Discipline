#include "edmesh.h"

#include "GeometricObjects.h"
#include <vector>

//#define drawArrays
#define drawAxis

#define max_value +1.9999e19
#define min_value -1.9999e-19

EDMesh::EDMesh(void) :  GObject("")
{ 
	trianglesCount = -1;
	nodesCount = 0;
	nodesActualCount = 0;
	visible = true;
}

EDMesh::EDMesh(const char* identifier) :  GObject(identifier)
{ 
	trianglesCount = -1;
	nodesCount = 0;
	nodesActualCount = 0;
	visible = true;
}

EDMesh::EDMesh(const char* identifier, char* path, char* filename) : GObject(identifier)
{
	char filepath[256];
	sprintf(filepath,"%s%s",path, filename);

	FILE* fileHandle = fopen(filepath, "rb");
	fseek(fileHandle, 0, SEEK_END);
	long fileSize = ftell(fileHandle);
	long filePos = 0;
	fseek(fileHandle, filePos, SEEK_SET);

	char line[256];
	char buffer[4096];
	int ret = 0;
	int state = 0;
	std::vector<EDPoint> vertexes;
	std::vector<EDPoint> faces;

#pragma region reading file
	float x = 0;
	float y = 0; 
	float z = 0;

	int fa = 0;
	int fb = 0;
	int fc = 0;
	int fd = 0;
	int fe = 0;
	int ff = 0;
	int fg = 0;
	int fh = 0;

	int lineNumber = 0;

	printf("Estado %d\n",state);
    while(!feof(fileHandle))
    {
        memset(buffer, 0, 4096);
        ret = fscanf(fileHandle, "%4095[^\n]\n", buffer);

		sscanf(buffer, "%s", line);
		lineNumber++;
		
		switch(state)
		{
		case 0:
			if(line[0] != '#')
			{
				state = 1;
				printf("Estado %d\n",state);
				break;
			}
			break;
		case 1:
			if(line[0] != 'm')
			{
				state = 2;
				printf("Estado %d\n",state);
				break;
			}
		case 2:
			if(line[0] == 'v' && line[1] != 't')
			{
				//Reading vertexes
				sscanf(buffer, "v %f %f %f", &x, &y, &z);
				vertexes.push_back(EDPoint(x,y,z));
				break;
			}		
			else
			{
				state = 3;
				printf("Estado %d\n",state);
			}
			break;
		case 3:
			//Jumping vt lines
			if(line[0] == 'f')
			{
				state = 4;
				printf("Estado %d\n",state);
			}
		case 4:
			//Reading faces
			if(ret != EOF && line[0] == 'f')
			{
				std::string str(buffer);
				size_t county = 0;
				int value = str.find_first_of('/');
				if(value != -1)
				{
					county = count(str.begin(), str.end(), '/');

					if(county == 3)
					{
						sscanf(buffer, "%s %d/%d %d/%d %d/%d", line, &fa,&fe,&fb,&ff,&fc,&fg,&fd,&fh);

						faces.push_back(EDPoint(fa,fb,fc));
						faces.push_back(EDPoint(fc,fd,fa));
					}
					else
					{
						sscanf(buffer, "%s %d/%d %d/%d %d/%d", line, &fa,&fe,&fb,&ff,&fc,&fg);

						faces.push_back(EDPoint(fa,fb,fc));
					}
				}
				else
				{
					county = count(str.begin(), str.end(), ' ');

					if(county == 3)
					{
						sscanf(buffer, "%s %d %d %d", line, &fa,&fb,&fc);

						faces.push_back(EDPoint(fa,fb,fc));
					}
					else
					{
						sscanf(buffer, "%s %d %d %d %d", line, &fa,&fb,&fc,&fd);

						faces.push_back(EDPoint(fa,fb,fc));
						faces.push_back(EDPoint(fc,fd,fa));
					}
				}
			}
			break;
		}
	}
#pragma endregion

	fclose(fileHandle);

	int vertexesSize = vertexes.size();
	printf("Finished reading!\n");

	trianglesCount = faces.size();
	triangles = new EDTriangle[trianglesCount];
	int index = 0;
	int k = 0;
	for(int i = 0; i < trianglesCount; i++)
	{
		EDPoint point = faces.at(i);
		
		EDPoint p1, p2, p3;
		p1 = vertexes.at((int)point.x - 1);
		p2 = vertexes.at((int)point.y - 1);
		p3 = vertexes.at((int)point.z - 1);

		triangles[index] = EDTriangle(p1,p2,p3);
		index++;
	}

	nodesCount = 0;
	nodesActualCount = 0;
	calculateCenter();
	visible = true;
}

EDMesh::EDMesh(const char* identifier, std::vector<EDTriangle*> triangles) : GObject(identifier)
{
	trianglesVector = triangles;
	initializeByVector();
	height = 0;
	visible = true;
}

EDMesh::~EDMesh(void)
{
	if(triangles && trianglesCount != -1)
		delete[] triangles;
}

void EDMesh::initializeByVector(void)
{
	trianglesCount = trianglesVector.size();
	int index = 0;

	this->triangles = new EDTriangle[trianglesCount];
	for(int i = 0; i < trianglesCount; i++)
	{
		EDTriangle* triangle = trianglesVector.at(i);
		this->triangles[i] = EDTriangle(triangle->p1, triangle->p2, triangle->p3);
		EDPoint p1, p2, p3;
		p1 = triangle->p1;
	}

	nodesCount = 0;
	nodesActualCount = 0;

	calculateCenter();

	moveAxis = EDPoint(max.x, max.y, max.z);
	selfAxis = EDPoint(min.x, min.y, min.z);

	centerAxis = EDPoint((max.x + min.x)/2.f, (max.y + min.y)/2.f, (max.z + min.z)/2.f);
	visible = true;
}

void EDMesh::draw(void)
{ 
	if(visible)
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
		EDPoint normal = EDPoint(0,0,0);
		for(int i = 0; i < trianglesCount;)
		{
			normal = triangles[i].getNormal();
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(triangles[i].p1.x, triangles[i].p1.y, triangles[i].p1.z);
			glVertex3f(triangles[i].p2.x, triangles[i].p2.y, triangles[i].p2.z);
			glVertex3f(triangles[i].p3.x, triangles[i].p3.y, triangles[i].p3.z);
			i++;
		}
		glEnd();
	
#ifdef drawAxis
		float aux = 0.0f;
		GCube cube = GCube("ccenter", 
			new EDPoint(moveAxis.x - 0.1, moveAxis.y - 0.1, moveAxis.z - 0.1 + aux),  
			new EDPoint(moveAxis.x + 0.1, moveAxis.y + 0.1, moveAxis.z + 0.1 + aux));
		cube.setMaterial(ambientMaterial, diffuseMaterial);
		cube.draw();

		GCube cube2 = GCube("cccenter", 
			new EDPoint(selfAxis.x - 0.1, selfAxis.y - 0.1, selfAxis.z - 0.1 + aux),  
			new EDPoint(selfAxis.x + 0.1, selfAxis.y + 0.1, selfAxis.z + 0.1 + aux));
		cube2.setMaterial(ambientMaterial, diffuseMaterial);
		cube2.draw();
#endif
#endif
	}
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
	for(int i = 0; i < trianglesCount; i++)
	{
		triangles[i].translate(toPoint);
	}

	moveAxis.translateTo(&toPoint);
	selfAxis.translateTo(&toPoint);
	centerAxis.translateTo(&toPoint);

	if(nodesCount != 0)
	{
		for(int i = 0; i < nodesActualCount; i++)
		{
			nodes[i]->translate(toPoint);
		}
	}
	
	calculateCenter();
}

void EDMesh::rotate(EDPoint axis, float angle)
{
	//EDPoint oldCenter = EDPoint(moveAxis.x, moveAxis.y, moveAxis.z);
	for(int i = 0; i < trianglesCount; i++)
	{
		triangles[i].rotate(axis, selfAxis, angle);
	}
	moveAxis.rotateTo(&selfAxis, axis, angle);

	//EDPoint translateDirection = EDPoint(moveAxis.x - oldCenter.x, moveAxis.y - oldCenter.y, moveAxis.z - oldCenter.z);
	if(nodesCount != 0)
	{
		for(int i = 0; i < nodesActualCount; i++)
		{
			EDPoint oldTestCenter = EDPoint(nodes[i]->selfAxis.x, nodes[i]->selfAxis.y, nodes[i]->selfAxis.z);
			EDPoint moveTestCenter = EDPoint(nodes[i]->selfAxis.x, nodes[i]->selfAxis.y, nodes[i]->selfAxis.z);
			moveTestCenter.rotateTo(&selfAxis, axis, angle);

			moveTestCenter = EDPoint(moveTestCenter.x - oldTestCenter.x, moveTestCenter.y - oldTestCenter.y, moveTestCenter.z - oldTestCenter.z);

			nodes[i]->translate(moveTestCenter);
			nodes[i]->rotate(axis, angle);
		}
	}
}

void EDMesh::scale(EDPoint axis, float factor)
{
	for(int i = 0; i < trianglesCount; i++)
	{
		triangles[i].scale(axis, centerAxis, factor);
	}

	if(nodesCount != 0)
	{
		for(int i = 0; i < nodesActualCount; i++)
		{
			nodes[i]->scale(axis, factor);
		}
	}

	calculateCenter();
}

void EDMesh::updateMinValue(void)
{
	EDPoint p1, p2, p3;
	p1 = triangles[0].p1;
	min = EDPoint(p1.x, p1.y, p1.z);
	for(int i = 0; i < trianglesCount; i++)
	{
		p1 = triangles[i].p1;
		if(p1.x < min.x)
		{
			min.x = p1.x;
		}
		if(p1.y < min.y)
		{
			min.y = p1.y;
		}
		if(p1.z < min.z)
		{
			min.z = p1.z;
		}
		p2 = triangles[i].p2;
		if(p2.x < min.x)
		{
			min.x = p2.x;
		}
		if(p2.y < min.y)
		{
			min.y = p2.y;
		}
		if(p2.z < min.z)
		{
			min.z = p2.z;
		}
		p3 = triangles[i].p3;
		if(p3.x < min.x)
		{
			min.x = p3.x;
		}
		if(p3.y < min.y)
		{
			min.y = p3.y;
		}
		if(p3.z < min.z)
		{
			min.z = p3.z;
		}
	}
}

void EDMesh::calculateCenter(void)
{
	EDPoint p1, p2, p3;
	p1 = triangles[0].p1;
	min = EDPoint(p1.x, p1.y, p1.z);
	max = EDPoint(p1.x, p1.y, p1.z);

#pragma region get min and maxx
	for(int i = 0; i < trianglesCount; i++)
	{
		p1 = triangles[i].p1;
		if(p1.x < min.x)
		{
			min.x = p1.x;
		}
		if(p1.y < min.y)
		{
			min.y = p1.y;
		}
		if(p1.z < min.z)
		{
			min.z = p1.z;
		}
		if(p1.x > max.x)
		{
			max.x = p1.x;
		}
		if(p1.y > max.y)
		{
			max.y = p1.y;
		}
		if(p1.z > max.z)
		{
			max.z = p1.z;
		}

		p2 = triangles[i].p2;
		if(p2.x < min.x)
		{
			min.x = p2.x;
		}
		if(p2.y < min.y)
		{
			min.y = p2.y;
		}
		if(p2.z < min.z)
		{
			min.z = p2.z;
		}
		if(p2.x > max.x)
		{
			max.x = p2.x;
		}
		if(p2.y > max.y)
		{
			max.y = p2.y;
		}
		if(p2.z > max.z)
		{
			max.z = p2.z;
		}

		p3 = triangles[i].p3;
		if(p3.x < min.x)
		{
			min.x = p3.x;
		}
		if(p3.y < min.y)
		{
			min.y = p3.y;
		}
		if(p3.z < min.z)
		{
			min.z = p3.z;
		}
		if(p3.x > max.x)
		{
			max.x = p3.x;
		}
		if(p3.y > max.y)
		{
			max.y = p3.y;
		}
		if(p3.z > max.z)
		{
			max.z = p3.z;
		}
	}
#pragma endregion

	float width = max.x - min.x;
	height = max.y - min.y;
	float depth = max.z - min.z;

	//center = EDPoint(min.x, min.y, min.z);
}

void EDMesh::instantiateNodes(int count)
{
	nodes = new EDMesh*[count];
	nodesCount = count;
}

void EDMesh::addNode(int position, EDMesh* mesh)
{
	if(position < 0 || position > nodesCount + 1)
		return;

	nodes[position] = mesh;
	nodesActualCount++;
}