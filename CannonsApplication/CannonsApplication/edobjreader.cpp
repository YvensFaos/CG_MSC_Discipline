#include "edobjreader.h"

#include <stdio.h>
#include <list>
#include <string>

#include "edgeom.h"

EDObjReader::EDObjReader(char* path, char* filename)
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
	std::list<EDPoint*> vertexes;
	std::list<EDPoint*> faces;
	std::list<EDTriangle*> objects;

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

	int lineNumber = 0;

	printf("Estado %d\n",state);
    while(!feof(fileHandle))
    {
        memset(buffer, 0, 4096);
        ret = fscanf(fileHandle, "%4095[^\n]\n", buffer);

		sscanf(buffer, "%s", line);
		lineNumber++;
		//printf("Estado %d. Line > %s\n",state, buffer);
		
		switch(state)
		{
		case 0:
			if(line[0] != '#')
			{
				state = 1;
				printf("Estado %d\n",state);
			}
			break;
		case 1:
			if(line[0] != 'm')
			{
				state = 2;
				printf("Estado %d\n",state);
			}
			break;
		case 2:
			if(line[0] == 'v' && line[1] != 't')
			{
				//Reading vertexes
				sscanf(buffer, "v %f %f %f", &x, &y, &z);
				vertexes.push_back(new EDPoint(x,y,z));
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
			break;
		case 4:
			//Reading faces
			if(ret != EOF && line[0] == 'f')
			{
				std::string str(buffer);
				int value = str.find_first_of('/');
				if(value != -1)
				{
					sscanf(buffer, "%s %d/%d %d/%d %d/%d", line, &fa,&fb,&fc,&fd,&fe,&ff);

					faces.push_back(new EDPoint(fa,fb,fc));
					faces.push_back(new EDPoint(fd,fe,ff));
				}
				else
				{
					sscanf(buffer, "%s %d %d %d", line, &fa,&fb,&fc);

					faces.push_back(new EDPoint(fa,fb,fc));
				}
			}
			break;
		}
	}
#pragma endregion
    
	vertexesSize = vertexes.size();
	printf("Finished reading!\n");
	vertexesArray = new EDPoint[vertexesSize];
	std::list<EDPoint*>::iterator i;
	int index = 0;
	for (i = vertexes.begin(); i != vertexes.end(); i++)
	{
		vertexesArray[index++] = *(*i);
	}

	trianglesSize = faces.size();
	triangles = new EDTriangle[trianglesSize];
	index = 0;
	for (i = faces.begin(); i != faces.end(); i++)
	{
		EDPoint point = *(*i);
		
		EDPoint p1, p2, p3;
		p1 = vertexesArray[(int)point.x - 1];
		p2 = vertexesArray[(int)point.y - 1];
		p3 = vertexesArray[(int)point.z - 1];

		triangles[index++] = EDTriangle(p1,p2,p3);
	}
}

EDObjReader::~EDObjReader(void)
{ 
	if(vertexesArray)
		delete[] vertexesArray;
	if(triangles)
		delete[] triangles;
}