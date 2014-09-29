#include "articulatedLuxorScene.h"

#include "edgroupedmesh.h"

void testMethod(float elapsedTime, GObject* object)
{
	EDGroupedMesh* luxor = (EDGroupedMesh*)object;

	//EDMesh* base = luxor->getGroup("Base");
	//base->translate(EDPoint(0.0f, -base->min.y, 0.0f));
	luxor->scale(EDPoint(0.f,1.f,0.f), 0.9f);
}

void testMethod2(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;

	luxor->rotate(EDPoint(0.f,1.f,0.f), 0.1f);
}

ArticulatedLuxorScene::ArticulatedLuxorScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.4f, 2.5f, 10.79f), new EDPoint(0.41f, 1.5f, 5.79f), 0.05f, 300.0f, 45.0f);

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

	//luxor->getGroup("Base")->rotate(EDPoint(0.f,1.f,0.f), -90.f);
	//luxor->rotate(EDPoint(0.f,1.f,0.f), -90.f);
	//luxor->setCallUpdate(testMethod);
	luxor->setCallUpdate(testMethod);

	scenario->objects.push_back(luxor);
}

ArticulatedLuxorScene::~ArticulatedLuxorScene(void)
{ }