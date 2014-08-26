#include "loadObjScene.h"

#include "edmesh.h"

LoadObjScene::LoadObjScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(40.0f, 34.2f, 90.0f), new EDPoint(40.0f, 30.0f, 75.0f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();
	GPlane* terrain = new GPlane("plano1", 20.0f, 90.0f, new EDPoint(-5.0f, 0.0f, -1.0f), new EDPlane());
	GLfloat ambientMaterial[] = {.2f, .8f, .1f, 0.9f};
	GLfloat diffuseMaterial[] = {.1f, .0f, .4f, 0.4f};
	terrain->setMaterial(ambientMaterial, diffuseMaterial);
	scenario->objects.push_back(terrain);

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* filename = "bullet.txt";

	EDMesh* mesh = new EDMesh("ball", path, filename);
	GLfloat ambientMaterial2[] = {.2f, .8f, .1f, 0.9f};
	GLfloat diffuseMaterial2[] = {.1f, .0f, .4f, 0.4f};
	mesh->setMaterial(ambientMaterial2, diffuseMaterial2);
	scenario->objects.push_back(mesh);


}

LoadObjScene::~LoadObjScene(void)
{ }