#include "edgroupedmesh.h"

EDGroupedMesh::EDGroupedMesh(const char* identifier) : GObject(identifier)
{ }

EDGroupedMesh::EDGroupedMesh(const char* identifier, char* path, char* filename) : GObject(identifier)
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

	EDMesh* actualMesh;

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
				vertexes.push_back(EDPoint(x,y,z));
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

						EDPoint* p1;
						EDPoint* p2;
						EDPoint* p3;
						p1 = &vertexes.at(fa - 1);
						p2 = &vertexes.at(fb - 1);
						p3 = &vertexes.at(fc - 1);

						actualMesh->trianglesVector.push_back(new EDTriangle(EDPoint(p1->x, p1->y, p1->z), EDPoint(p2->x, p2->y, p2->z), EDPoint(p3->x, p3->y, p3->z)));
					}
					else
					{
						sscanf(buffer, "%s %d %d %d %d", line, &fa,&fb,&fc,&fd);

						faces.push_back(EDPoint(fa,fb,fc));
						faces.push_back(EDPoint(fc,fd,fa));
					}
				}
			}
			else
			{
				if(line[0] == 'g')
				{
					char group[256];
					sscanf(buffer, "g %s", group);

					if(meshes.find(group) == meshes.end())
					{
						meshes[group] = EDMesh(group);
						groups.push_back(group);
					}

					actualMesh = &meshes[group];
				}
			}
			break;
		}
	}
#pragma endregion

	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].initializeByVector();
	}
}

void EDGroupedMesh::draw(void)
{
	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].draw();
	}
}

void EDGroupedMesh::update(float elapsedTime)
{
	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].update(elapsedTime);
	}
}

void EDGroupedMesh::setMaterial(GLfloat* ambient, GLfloat* diffuse)
{
	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].setMaterial(ambient, diffuse);
	}
}

void EDGroupedMesh::translate(EDPoint toPoint)
{
	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].translate(toPoint);
	}
}

void EDGroupedMesh::rotate(EDPoint axis, float angle)
{
	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].rotate(axis, angle);
	}
}

void EDGroupedMesh::scale(EDPoint axis, float factor)
{
	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].scale(axis, factor);
	}
}

void EDGroupedMesh::updateMinValue(void)
{
	for(int i = 0; i < groups.size(); i++)
	{
		std::string grp = groups.at(i);

		meshes[grp].updateMinValue();
	}
}

EDMesh* EDGroupedMesh::getGroup(char* group)
{
	return &meshes[group];
}