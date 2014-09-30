#include "articulatedLuxorScene.h"

#include "edgroupedmesh.h"

void testMethod(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;
	float factor = 0.001;
	luxor->floatCounter += factor;
	luxor->translate(EDPoint(0.f,0.f,-factor));

	printf("F = %4.2f\n", luxor->floatCounter);
}

void testMethod2(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;
	float factor = 0.1;
	luxor->floatCounter += factor;
	//luxor->translate(EDPoint(0.f,0.f,-factor));
	luxor->rotate(EDPoint(1.f,0.f,0.f), -factor);

	printf("F = %4.2f\n", luxor->floatCounter);
}

ArticulatedLuxorScene::ArticulatedLuxorScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.4f, 2.5f, 10.79f), new EDPoint(0.41f, 1.5f, 5.79f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
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
	luxor->scale(EDPoint(0.f,1.f,0.f), 1.0f);
	
	luxor->getGroup("Base")->instantiateNodes(1);
	luxor->getGroup("Base")->addNode(0, luxor->getGroup("L1"), EDPoint(0.0f, 0.0f, 0.0f));

	luxor->getGroup("L1")->instantiateNodes(1);
	luxor->getGroup("L1")->addNode(0, luxor->getGroup("L2"), EDPoint(0.0f, 0.0f, 0.0f));

	luxor->getGroup("L2")->instantiateNodes(1);
	luxor->getGroup("L2")->addNode(0, luxor->getGroup("L3"), EDPoint(0.0f, 5.5f,-1.0f));

	//luxor->getGroup("Base")->rotate(EDPoint(0.f,1.f,0.f), 45.f);
	//luxor->getGroup("L1")->rotate(EDPoint(0.f,1.f,0.f), 45.f);

	luxor->getGroup("Base")->center.print();
	//luxor->getGroup("Base")->setCallUpdate(testMethod);
	luxor->getGroup("L1")->center.print();
	luxor->getGroup("L2")->center.print();

	//luxor->getGroup("L3")->rotate(EDPoint(1.f,0.f,0.f), 45.f);
	luxor->getGroup("L3")->setCallUpdate(testMethod2);

	//luxor->getGroup("L2")->floatCounter = 0.f;
	//luxor->getGroup("L2")->rotate(EDPoint(0.f,1.f,0.f), 45.f);
	//luxor->getGroup("L2")->translate(EDPoint(0.6f,0.f,-2.03f));
	//luxor->getGroup("L3")->rotate(EDPoint(0.f,1.f,0.f), -90.f);
	//luxor->getGroup("L2")->setCallUpdate(testMethod);

	scenario->objects.push_back(luxor);
}

ArticulatedLuxorScene::~ArticulatedLuxorScene(void)
{ }