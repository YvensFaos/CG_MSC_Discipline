#include "articulatedLuxorScene.h"

#include "edgroupedmesh.h"

void testMethodX(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;
	float factor = 0.05;
	luxor->floatCounter += factor;
	luxor->rotate(EDPoint(1.f,0.f, 0.f),-factor);
}

void testMethodY(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;
	float factor = 0.05;
	luxor->floatCounter += factor;
	luxor->rotate(EDPoint(0.f,1.f, 0.f),-factor);
}

void testMethodZ(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;
	float factor = 0.05;
	luxor->floatCounter += factor;
	luxor->rotate(EDPoint(0.f,0.f, 1.f),-factor);
}

void testMethod(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;
	switch(luxor->intCounter)
	{
	case 0:
		{
			//state 1:
			if(luxor->floatCounter < 0.5)
			{
				printf("f : %f\n", luxor->floatCounter);
				float factor = 0.001;
				luxor->floatCounter += factor;
				luxor->translate(EDPoint(-factor,0.f,0.f));
			}
			else
			{
				luxor->floatCounter = 0.f;
				luxor->intCounter = 1;
			}
		}
	}
}

ArticulatedLuxorScene::ArticulatedLuxorScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.1f, 4.89f, 10.58f), new EDPoint(0.11f, 3.89f, 5.59f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "simple_luxor.txt";

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
	//luxor->scale(EDPoint(0.f,1.f,0.f), 1.0f);
	
	EDMesh* base = luxor->getGroup("Base");
	r = (77/255.f);
	g = (20/255.f);
	b = (20/255.f);
	GLfloat ambientMaterial2[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (20/255.f);
	b = (20/255.f);
	GLfloat diffuseMaterial2[] = {r, g, b, 1.0f};
	base->setMaterial(ambientMaterial2, diffuseMaterial2);

	EDMesh* l1 = luxor->getGroup("L1");
	r = (20/255.f);
	g = (77/255.f);
	b = (20/255.f);
	GLfloat ambientMaterial3[] = {r, g, b, 1.0f};
	r = (20/255.f);
	g = (90/255.f);
	b = (20/255.f);
	GLfloat diffuseMaterial3[] = {r, g, b, 1.0f};
	l1->setMaterial(ambientMaterial3, diffuseMaterial3);

	EDMesh* l2 = luxor->getGroup("L2");
	r = (20/255.f);
	g = (20/255.f);
	b = (77/255.f);
	GLfloat ambientMaterial4[] = {r, g, b, 1.0f};
	r = (20/255.f);
	g = (20/255.f);
	b = (90/255.f);
	GLfloat diffuseMaterial4[] = {r, g, b, 1.0f};
	l2->setMaterial(ambientMaterial4, diffuseMaterial4);

	EDMesh* l3 = luxor->getGroup("L3");
	r = (77/255.f);
	g = (15/255.f);
	b = (77/255.f);
	GLfloat ambientMaterial5[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (15/255.f);
	b = (90/255.f);
	GLfloat diffuseMaterial5[] = {r, g, b, 1.0f};
	l3->setMaterial(ambientMaterial5, diffuseMaterial5);

	base->instantiateNodes(1);
	base->addNode(0, luxor->getGroup("L1"), EDPoint(0.0f, base->height/2.f, 0.0f));
	//base->setCallUpdate(testMethod2);

	l1->instantiateNodes(1);
	l1->addNode(0, luxor->getGroup("L2"), EDPoint(0.0f, l1->height/2.f, 0.0f));
	l2->selfAxis = l1->moveAxis;

	l2->instantiateNodes(1);
	l2->addNode(0, luxor->getGroup("L3"), EDPoint(0.0f, l2->height/2.f, 0.0f));
	l3->selfAxis = l2->moveAxis;

	//l1->rotate(EDPoint(0.0f, 0.f, 1.f), -10.f);
	//l2->rotate(EDPoint(0.0f, 0.f, 1.f), -30.f);
	//base->rotate(EDPoint(0.f, 1.f, 0.f), 90.f);

	//base->setCallUpdate(testMethodY);
	//l1->setCallUpdate(testMethodZ);
	//l2->setCallUpdate(testMethodX);
	//l3->setCallUpdate(testMethodX);
	//base->setCallUpdate(testMethod2);

	/*
	luxor->getGroup("Base")->instantiateNodes(1);
	luxor->getGroup("Base")->addNode(0, luxor->getGroup("L1"), EDPoint(0.0f, 0.0f, 0.0f));

	luxor->getGroup("L1")->instantiateNodes(1);
	luxor->getGroup("L1")->addNode(0, luxor->getGroup("L2"), EDPoint(0.0f, 0.0f, 0.0f));

	luxor->getGroup("L2")->instantiateNodes(1);
	luxor->getGroup("L2")->addNode(0, luxor->getGroup("L3"), EDPoint(0.0f, 5.5f,-1.0f));

	luxor->getGroup("Base")->rotate(EDPoint(0.f,1.f,0.f), 45.f);
	luxor->getGroup("L1")->rotate(EDPoint(0.f,1.f,0.f), 45.f);

	luxor->getGroup("Base")->center.print();
	luxor->getGroup("Base")->setCallUpdate(testMethod);
	luxor->getGroup("L1")->center.print();
	luxor->getGroup("L2")->center.print();
	
	luxor->getGroup("L3")->rotate(EDPoint(1.f,0.f,0.f), 45.f);
	luxor->getGroup("L3")->setCallUpdate(testMethod2);

	luxor->getGroup("L2")->floatCounter = 0.f;
	luxor->getGroup("L2")->rotate(EDPoint(0.f,1.f,0.f), 45.f);
	luxor->getGroup("L2")->translate(EDPoint(0.6f,0.f,-2.03f));
	luxor->getGroup("L3")->rotate(EDPoint(0.f,1.f,0.f), -90.f);
	luxor->getGroup("L2")->setCallUpdate(testMethod);
	*/

	scenario->objects.push_back(luxor);

	l1->rotate(EDPoint(0.0f, 0.f, 1.f), -30.f);
	l2->rotate(EDPoint(0.0f, 0.f, 1.f), 60.f);
	l3->rotate(EDPoint(0.0f, 0.f, 1.f), 60.f);
	base->setCallUpdate(testMethodY);
}

ArticulatedLuxorScene::~ArticulatedLuxorScene(void)
{ }