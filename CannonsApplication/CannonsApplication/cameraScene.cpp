#include "cameraScene.h"

#include "edmesh.h"

CameraScene::CameraScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(-0.19f, 2.29f, 43.8f), new EDPoint(-0.19f, 2.29f, 42.8f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();
	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "corridor.txt";

	EDMesh* table = new EDMesh("corridor", path, filename1);
	float r = (58/255.f);
	float g = (59/255.f);
	float b = (54/255.f);
	GLfloat ambientMaterial1[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (92/255.f);
	b = (84/255.f);
	GLfloat diffuseMaterial1[] = {r, g, b, 1.0f};
	table->setMaterial(ambientMaterial1, diffuseMaterial1);
	scenario->objects.push_back(table);
}

CameraScene::~CameraScene(void)
{ }