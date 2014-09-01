#include "loadObjScene.h"

#include "edmesh.h"

void rotateMeshOnXYZ(float elapsedTime, GObject* object)
{
	EDMesh* cube = (EDMesh*)object;
	object->floatCounter += (elapsedTime*0.5);
	
	float factor = 0.05f;

	cube->rotate(EDPoint(0.0f, 1.0f, 0.0f), factor);
}

void scaleMeshOnXYZ(float elapsedTime, GObject* object)
{
	EDMesh* cube = (EDMesh*)object;
	object->floatCounter += (elapsedTime*0.5);
	
	float factor = 1.000005f; //0.5f + sin(object->floatCounter);

	printf("scale factor: %f\n", factor);
	cube->scale(EDPoint(1.0f, 1.0f, 1.0f), factor);
}

LoadObjScene::LoadObjScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(7.3f, 3.3f, 9.0f), new EDPoint(-3.7f, 1.7f, -0.7f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename2 = "luxor3.txt";

	EDMesh* mesh1 = new EDMesh("luxor", path, filename2);
	GLfloat ambientMaterial3[] = {.8f, .4f, .1f, 1.0f};
	GLfloat diffuseMaterial3[] = {.4f, .3f, .4f, 1.0f};
	mesh1->setMaterial(ambientMaterial3, diffuseMaterial3);
	scenario->objects.push_back(mesh1);
	
	mesh1->setCallUpdate(rotateMeshOnXYZ);
}

LoadObjScene::~LoadObjScene(void)
{ }