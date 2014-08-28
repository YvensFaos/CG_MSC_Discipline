#include "loadObjScene.h"

#include "edmesh.h"

LoadObjScene::LoadObjScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(30.9f, 1.0f, 0.2f), new EDPoint(15.89f, -.4f, 0.2f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename = "corridor2.txt";
	char* filename2 = "luxor.txt";

	EDMesh* mesh = new EDMesh("corridor", path, filename);
	GLfloat ambientMaterial2[] = {.8f, .4f, .1f, 1.0f};
	GLfloat diffuseMaterial2[] = {.4f, .3f, .4f, 1.0f};
	mesh->setMaterial(ambientMaterial2, diffuseMaterial2);
	//scenario->objects.push_back(mesh);

	EDMesh* mesh1 = new EDMesh("luxor", path, filename2);
	GLfloat ambientMaterial3[] = {.8f, .4f, .1f, 1.0f};
	GLfloat diffuseMaterial3[] = {.4f, .3f, .4f, 1.0f};
	mesh1->setMaterial(ambientMaterial3, diffuseMaterial3);
	scenario->objects.push_back(mesh1);
}

LoadObjScene::~LoadObjScene(void)
{ }