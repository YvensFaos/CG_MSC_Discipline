#include "trinityScene.h"

#include "edgroupedmesh.h"

void luxorAnimation02(float elapsedTime, GObject* object)
{
	EDGroupedMesh* luxor = (EDGroupedMesh*)object;
	/*EDMesh* base = luxor->getGroup("Base");
	EDMesh* l1 = luxor->getGroup("L1");
	EDMesh* l2 = luxor->getGroup("L2");
	EDMesh* l3 = luxor->getGroup("L3");*/
}

void testMethodRotationBaby(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;
	float factor = 0.1;
	luxor->floatCounter += factor;
	luxor->rotate(EDPoint(1.f,0.f, 0.f),-factor);
}


TrinityScene::TrinityScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(-7.78f, 0.34f, 0.76f), new EDPoint(-2.87f, -0.65f, -0.9f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "human.txt";

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
	
	EDMesh* cintura = luxor->getGroup("Cintura");
	cintura->visible = true;
	EDMesh* coxae = luxor->getGroup("Coxa.E");
	coxae->visible = true;
	EDMesh* coxad = luxor->getGroup("Coxa.D");
	coxad->visible = false;
	EDMesh* pernae = luxor->getGroup("Perna.E");
	pernae->visible = false;
	EDMesh* pernad = luxor->getGroup("Perna.D");
	pernad->visible = false;
	EDMesh* pee = luxor->getGroup("Pe.E");
	pee->visible = false;
	EDMesh* ped = luxor->getGroup("Pe.D");
	ped->visible = false;

	EDMesh* bracoe = luxor->getGroup("Braco.E");
	bracoe->visible = false;
	EDMesh* bracod = luxor->getGroup("Braco.D");
	bracod->visible = false;
	EDMesh* antee = luxor->getGroup("Ante.E");
	antee->visible = false;
	EDMesh* anted = luxor->getGroup("Ante.D");
	anted->visible = false;
	EDMesh* maoe = luxor->getGroup("Mao.E");
	maoe->visible = false;
	EDMesh* maod = luxor->getGroup("Mao.D");
	maod->visible = false;

	EDMesh* barriga = luxor->getGroup("Barriga");
	barriga->visible = true;
	EDMesh* peito = luxor->getGroup("Peito");
	peito->visible = true;
	EDMesh* cabeca = luxor->getGroup("Cabeca");
	cabeca->visible = false;

	cintura->instantiateNodes(3);
	cintura->selfAxis =    cintura->centerAxis;
	cintura->selfAxis.y -= cintura->height / 2.f;
	cintura->moveAxis =    cintura->centerAxis;
	cintura->moveAxis.y += cintura->height / 2.f;

	//EDPoint(0.0f, 0.0f, 0.0f);
	barriga->instantiateNodes(1);
	barriga->selfAxis =    cintura->centerAxis;
	barriga->selfAxis.y += cintura->height / 2.f;
	barriga->moveAxis =    barriga->centerAxis;
	barriga->moveAxis.y += barriga->height / 2.f;
	cintura->addNode(0, barriga);

	peito->selfAxis =    barriga->centerAxis;
	peito->selfAxis.y =  peito->min.y;
	peito->moveAxis =    peito->selfAxis;
	peito->moveAxis.y =  peito->min.y;
	barriga->addNode(0, peito);

	r = (77/255.f);
	g = (20/255.f);
	b = (20/255.f);
	GLfloat ambientMaterial2[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (20/255.f);
	b = (20/255.f);
	GLfloat diffuseMaterial2[] = {r, g, b, 1.0f};
	coxae->setMaterial(ambientMaterial2, diffuseMaterial2);

	//coxae->selfAxis    = coxae->centerAxis;
	//coxae->selfAxis.y += coxae->height / 2.f;
	coxae->selfAxis    = cintura->centerAxis;
	coxae->selfAxis.x =  coxae->centerAxis.x;
	coxae->selfAxis.y =  coxae->max.y;
	//coxae->selfAxis.y -= cintura->height / 2.f;
	//coxae->selfAxis.x -= 0.5f;
	//coxae->moveAxis =    cintura->selfAxis;
	//coxae->moveAxis.x -= 0.5f;
	cintura->addNode(1, coxae);

	//base->instantiateNodes(1);
	//base->addNode(0, luxor->getGroup("L1"), EDPoint(0.0f, base->height/2.f, 0.0f));
	//base->selfAxis = base->centerAxis;
	//base->selfAxis.y -= base->height / 2.f;
	//base->moveAxis = base->centerAxis;
	//base->moveAxis.y += base->height / 2.f;
	//l1->selfAxis = base->centerAxis;
	//l1->selfAxis.y += base->height / 2.f;

	//l1->instantiateNodes(1);
	//l1->addNode(0, luxor->getGroup("L2"), EDPoint(0.0f, l1->height/2.f, 0.0f));
	//l1->moveAxis = l1->centerAxis;
	//l1->moveAxis.y += l1->height / 2.f;
	//l2->selfAxis = l1->moveAxis;

	//l2->instantiateNodes(1);
	//l2->addNode(0, luxor->getGroup("L3"), EDPoint(0.0f, l2->height/2.f, 0.0f));
	//l2->moveAxis = l2->centerAxis;
	//l2->moveAxis.y += l2->height / 2.f;
	//l3->selfAxis = l2->moveAxis;

	cintura->setCallUpdate(testMethodRotationBaby);
	//coxae->setCallUpdate(testMethodRotationBaby);
	luxor->intCounter = 0; //Estado 0
	luxor->setCallUpdate(luxorAnimation02);
	scenario->objects.push_back(luxor);
}

TrinityScene::~TrinityScene(void)
{ }