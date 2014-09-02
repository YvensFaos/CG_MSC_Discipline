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
	
	float factor = 0.999995f; //0.5f + sin(object->floatCounter);

	printf("scale factor: %f\n", factor);
	cube->scale(EDPoint(1.0f, 1.0f, 1.0f), factor);
}

LoadObjScene::LoadObjScene(void) : Scene()
{
	/*
	2.6 5.0 8.1
	0.9 2.2 3.4
	*/
	camera = new EDCamera(new EDPoint(2.6f, 5.0f, 8.1f), new EDPoint(0.9f, 2.2f, 3.4f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "table3.txt";
	char* filename2 = "luxor3.txt";

	EDMesh* table = new EDMesh("table", path, filename1);
	GLfloat ambientMaterial1[] = {.35f, .35f, .35f, 1.0f};
	GLfloat diffuseMaterial1[] = {.35f, .35f, .35f, 1.0f};
	table->setMaterial(ambientMaterial1, diffuseMaterial1);
	scenario->objects.push_back(table);

	EDMesh* luxor = new EDMesh("luxor", path, filename2);
	GLfloat ambientMaterial3[] = {.15f, .15f, .15f, 1.0f};
	GLfloat diffuseMaterial3[] = {.20f, .20f, .20f, 1.0f};
	luxor->setMaterial(ambientMaterial3, diffuseMaterial3);
	luxor->scale(EDPoint(1.f,1.f,1.f), 0.9f);
	luxor->rotate(EDPoint(0.f,1.f,0.f), 90);
	luxor->translate(EDPoint(0.f,0.32f,0.f));
	scenario->objects.push_back(luxor);
	
	//luxor->setCallUpdate(rotateMeshOnXYZ);
	//luxor->setCallUpdate(scaleMeshOnXYZ);
}

LoadObjScene::~LoadObjScene(void)
{ }