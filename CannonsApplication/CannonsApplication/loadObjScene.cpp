#include "loadObjScene.h"

#include "edmesh.h"

LoadObjScene::LoadObjScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.0f, 1.4f, 42.0f), new EDPoint(0.0f, 2.0f, 27.0f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename = "corridor.txt";

	EDMesh* mesh = new EDMesh("corridor", path, filename);
	GLfloat ambientMaterial2[] = {.8f, .4f, .1f, 1.0f};
	GLfloat diffuseMaterial2[] = {.7f, .3f, .4f, 1.0f};
	mesh->setMaterial(ambientMaterial2, diffuseMaterial2);
	scenario->objects.push_back(mesh);
}

LoadObjScene::~LoadObjScene(void)
{ }