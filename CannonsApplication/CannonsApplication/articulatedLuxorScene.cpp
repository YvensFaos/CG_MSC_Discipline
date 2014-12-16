#include "articulatedLuxorScene.h"

#include "edgroupedmesh.h"

void normalCameraStopped(float elapsedTime, EDCamera* self)
{ }

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

void luxorAnimation01(float elapsedTime, GObject* object)
{
	EDGroupedMesh* luxor = (EDGroupedMesh*)object;
	EDMesh* base = luxor->getGroup("Base");
	EDMesh* l1 = luxor->getGroup("L1");
	EDMesh* l2 = luxor->getGroup("L2");
	EDMesh* l3 = luxor->getGroup("L3");

	switch(luxor->intCounter)
	{
	case 0:
		{
			//Levantando o corpo todo até 70º
			if(l1->floatCounter > 60.0)
			{
				float factor = 0.05;
				l1->floatCounter -= factor;
				l1->rotate(EDPoint(0.f, 0.f, 1.f), -factor);
			}
			else
			{
				luxor->intCounter++;
			}
		}
		break;
	case 1:
		{
			//Levantando o corpo em duas partes
			if(l1->floatCounter > 0.0)
			{
				float factor = 0.05;
				l1->floatCounter -= factor;
				l1->rotate(EDPoint(0.f, 0.f, 1.f), -factor);
				l2->rotate(EDPoint(0.f, 0.f, 1.f), -factor/1.8f);
			}
			else
			{
				luxor->intCounter++;
				l3->floatCounter = 0.0f;
			}
		}
		break;
	case 2:
		{
			//Ajustando a cabeça
			if(l3->floatCounter < 65.0)
			{
				float factor = 0.05;
				l3->floatCounter += factor;
				l3->rotate(EDPoint(0.f, 0.f, 1.f), -factor);
			}
			else
			{
				luxor->intCounter++;
				base->floatCounter = 0;
			}
		}
		break;
	case 3:
		{
			//Andando no X
			if(base->floatCounter < 5.0)
			{
				float factor = 0.001;
				base->floatCounter += factor;
				base->translate(EDPoint(factor, 0.f, 0.f));
			}
			else
			{
				luxor->intCounter++;
				base->floatCounter = 0;
			}
		}
		break;
	case 4:
		{
			//Rotacionando em torno do Y
			if(base->floatCounter < 90.0)
			{
				float factor = 0.05;
				base->floatCounter += factor;
				base->rotate(EDPoint(0.f, 1.f, 0.f), factor);
			}
			else
			{
				luxor->intCounter++;
				base->floatCounter = 0;
			}
		}
		break;
	case 5:
		{
			//Andando no Z
			if(base->floatCounter < 5.0)
			{
				float factor = 0.001;
				base->floatCounter += factor;
				base->translate(EDPoint(0.f, 0.f, -factor));
			}
			else
			{
				luxor->intCounter++;
				l1->floatCounter = 0;
			}
		}
		break;
	case 6:
		{
			//Rotaciona em torno da base
			if(l1->floatCounter < 90.0)
			{
				float factor = 0.05;
				l1->floatCounter += factor;
				l1->rotate(EDPoint(0.f, 1.f, 0.f), factor);
			}
			else
			{
				luxor->intCounter++;
				l2->floatCounter = 0;
			}
		}
		break;
	case 7:
		{
			//Rotaciona em torno da base
			if(l2->floatCounter < 20.0)
			{
				float factor = 0.05;
				l2->floatCounter += factor;
				l2->rotate(EDPoint(0.f, 0.f, 1.f), factor);
			}
			else
			{
				luxor->intCounter++;
				l2->floatCounter = 0;
			}
		}
		break;
	}
}

ArticulatedLuxorScene::ArticulatedLuxorScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(1.8f, 4.89f, 10.58f), new EDPoint(1.81f, 3.89f, 5.59f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
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
	base->addNode(0, luxor->getGroup("L1"));
	base->selfAxis = base->centerAxis;
	base->selfAxis.y -= base->height / 2.f;
	base->moveAxis = base->centerAxis;
	base->moveAxis.y += base->height / 2.f;

	l1->selfAxis = base->centerAxis;
	l1->selfAxis.y += base->height / 2.f;

	l1->instantiateNodes(1);
	l1->addNode(0, luxor->getGroup("L2"));
	l1->moveAxis = l1->centerAxis;
	l1->moveAxis.y += l1->height / 2.f;
	l2->selfAxis = l1->moveAxis;

	l2->instantiateNodes(1);
	l2->addNode(0, luxor->getGroup("L3"));
	l2->moveAxis = l2->centerAxis;
	l2->moveAxis.y += l2->height / 2.f;
	l3->selfAxis = l2->moveAxis;

	camera->setCallUpdate(normalCameraStopped);
	scenario->objects.push_back(luxor);

	//Início
	l1->rotate(EDPoint(0.0f, 0.f, 1.f), 90.f);

	luxor->setCallUpdate(luxorAnimation01);
	luxor->intCounter = 0; //Estado 0
	l1->floatCounter = 90.f;
}

ArticulatedLuxorScene::~ArticulatedLuxorScene(void)
{ }