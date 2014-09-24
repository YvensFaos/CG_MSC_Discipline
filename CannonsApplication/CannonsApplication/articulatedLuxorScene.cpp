#include "articulatedLuxorScene.h"

#include "edgroupedmesh.h"

ArticulatedLuxorScene::ArticulatedLuxorScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.4f, 2.5f, 6.59f), new EDPoint(0.41f, 1.5f, 1.6f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "luxor_204.txt";
	char* filename2 = "luxor_203.txt";

	float r, g, b;
	EDGroupedMesh* luxor = new EDGroupedMesh("luxor", path, filename1);
	r = (77/255.f);
	g = (78/255.f);
	b = (62/255.f);
	GLfloat ambientMaterial1[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (92/255.f);
	b = (84/255.f);
	GLfloat diffuseMaterial1[] = {r, g, b, 1.0f};
	luxor->setMaterial(ambientMaterial1, diffuseMaterial1);
	scenario->objects.push_back(luxor);

	/*
	luxor->scale(EDPoint(1.f,1.f,1.f), 0.9f);
	luxor->rotate(EDPoint(0.f,1.f,0.f), 60);
	luxor->translate(EDPoint(-.6f,3.25f,2.5f));
	luxor->updateMinValue();

	EDMesh* luxor1 = new EDMesh("luxor1", path, filename2);
	r = (77/255.f);
	g = (78/255.f);
	b = (62/255.f);
	GLfloat ambientMaterial3[] = {r, g, b, 1.0f};
	r = (207/255.f);
	g = (226/255.f);
	b = (198/255.f);
	GLfloat diffuseMaterial3[] = {r, g, b, 1.0f};
	luxor1->setMaterial(ambientMaterial3, diffuseMaterial3);
	luxor1->scale(EDPoint(1.f,1.f,1.f), 0.9f);
	luxor1->rotate(EDPoint(0.f,1.f,0.f), 60);
	luxor1->translate(EDPoint(-.6f,3.25f,2.5f));
	luxor1->updateMinValue();
	scenario->objects.push_back(luxor1);
	*/
}

ArticulatedLuxorScene::~ArticulatedLuxorScene(void)
{ }