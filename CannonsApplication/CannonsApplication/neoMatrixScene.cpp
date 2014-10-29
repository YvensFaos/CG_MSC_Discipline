#include "neoMatrixScene.h"

#include "edgroupedmesh.h"

void neoAnimation(float elapsedTime, GObject* object)
{
	EDGroupedMesh* neo = (EDGroupedMesh*)object;
	EDMesh* cintura = neo->getGroup("Cintura");
	EDMesh* coxae = neo->getGroup("Coxa.E");
	EDMesh* coxad = neo->getGroup("Coxa.D");
	EDMesh* pernae = neo->getGroup("Perna.E");
	EDMesh* pernad = neo->getGroup("Perna.D");
	EDMesh* pee = neo->getGroup("Pe.E");
	EDMesh* ped = neo->getGroup("Pe.D");
	EDMesh* bracoe = neo->getGroup("Braco.E");
	EDMesh* bracod = neo->getGroup("Braco.D");
	EDMesh* antee = neo->getGroup("Ante.E");
	EDMesh* anted = neo->getGroup("Ante.D");
	EDMesh* maoe = neo->getGroup("Mao.E");
	EDMesh* maod = neo->getGroup("Mao.D");
	EDMesh* barriga = neo->getGroup("Barriga");
	EDMesh* peito = neo->getGroup("Peito");
	EDMesh* cabeca = neo->getGroup("Cabeca");

	neo->floatCounter += elapsedTime;
	
}

void testCameraUpdate2(float elapsedTime, EDCamera* self)
{
	self->timer += elapsedTime;

	/*
	switch(self->intCounter)
	{
	case 0:
		if(self->position->z < 14.f)
		{
			self->translateTo(new EDPoint(0.f, 0.f, 0.05f));
		}
		else
		{
			self->lookAt = new EDPoint(0.0f, -0.752869487, -0.153204992);
			self->intCounter++;
		}
		break;
	case 1:
		{
			if(self->floatCounter < 310.0f)
			{
				float factor = 2.5f;
				self->floatCounter += factor;
				self->rotateToLookAt(EDPoint::Y, factor);
				self->translateTo(new EDPoint(0.f, 0.01f, 0.f));
				self->zoomIn();
			}
			else
			{
				self->intCounter++;
			}
		}
		break;
	case 2:
		{
			if(self->timer > 3.6f)
			{
				self->intCounter++;
			}
		}
		break;
	case 3:
		{
			if(self->timer < 4.5f)
			{
				self->zoomOut();
				self->zoomOut();
				self->zoomOut();
				self->rotateToLookAt(EDPoint::Y, 1.25f);
			}
		}
		break;
	}*/

	
}

NeoMatrixScene::NeoMatrixScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.0f, -0.75f, -13.5), new EDPoint(0.0f, -0.75f, -4.2f), 0.05f, 300.0f, 45.0f);
	camera->intCounter = 0;
	camera->floatCounter = 0.0f;
	camera->timer = 0.0f;
	camera->setCallUpdate(testCameraUpdate2);
	scenario = new Scenario();

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
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

	r = (20/255.f);
	g = (20/255.f);
	b = (20/255.f);
	GLfloat ambientTuxedo[] = {r, g, b, 1.0f};
	r = (38/255.f);
	g = (47/255.f);
	b = (44/255.f);
	GLfloat diffuseTuxedo[] = {r, g, b, 1.0f};
	
#pragma region carregando pedaços do modelo
	EDMesh* cintura = luxor->getGroup("Cintura");
	cintura->visible = true;
	cintura->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* coxae = luxor->getGroup("Coxa.E");
	coxae->visible = true;
	coxae->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* coxad = luxor->getGroup("Coxa.D");
	coxad->visible = true;
	coxad->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* pernae = luxor->getGroup("Perna.E");
	pernae->visible = true;
	EDMesh* pernad = luxor->getGroup("Perna.D");
	pernad->visible = true;
	EDMesh* pee = luxor->getGroup("Pe.E");
	pee->visible = true;
	pee->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* ped = luxor->getGroup("Pe.D");
	ped->visible = true;
	ped->setMaterial(ambientTuxedo, diffuseTuxedo);

	EDMesh* bracoe = luxor->getGroup("Braco.E");
	bracoe->visible = true;
	bracoe->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* bracod = luxor->getGroup("Braco.D");
	bracod->visible = true;
	bracod->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* antee = luxor->getGroup("Ante.E");
	antee->visible = true;
	EDMesh* anted = luxor->getGroup("Ante.D");
	anted->visible = true;
	EDMesh* maoe = luxor->getGroup("Mao.E");
	maoe->visible = true;
	maoe->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* maod = luxor->getGroup("Mao.D");
	maod->visible = true;
	maod->setMaterial(ambientTuxedo, diffuseTuxedo);

	EDMesh* barriga = luxor->getGroup("Barriga");
	barriga->visible = true;
	barriga->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* peito = luxor->getGroup("Peito");
	peito->visible = true;
	peito->setMaterial(ambientTuxedo, diffuseTuxedo);
	EDMesh* cabeca = luxor->getGroup("Cabeca");
	cabeca->visible = true;
#pragma endregion

#pragma region cintura barriga peito cabeca
	cintura->instantiateNodes(3);
	cintura->selfAxis =    cintura->centerAxis;
	cintura->selfAxis.y -= cintura->height / 2.f;

	barriga->instantiateNodes(1);
	barriga->selfAxis =    cintura->centerAxis;
	barriga->selfAxis.y += cintura->height / 2.f;
	cintura->addNode(0, barriga);

	peito->instantiateNodes(3);
	peito->selfAxis =    barriga->centerAxis;
	peito->selfAxis.y =  peito->min.y;
	barriga->addNode(0, peito);

	cabeca->selfAxis = cabeca->centerAxis;
	cabeca->selfAxis.y = peito->max.y;
	peito->addNode(0, cabeca);
#pragma endregion

#pragma region perna esquerda
	coxae->selfAxis    = cintura->centerAxis;
	coxae->selfAxis.x =  coxae->centerAxis.x;
	coxae->selfAxis.y =  coxae->max.y;
	cintura->addNode(1, coxae);

	coxae->instantiateNodes(1);
	pernae->selfAxis    = pernae->centerAxis;
	pernae->selfAxis.y =  pernae->max.y;
	coxae->addNode(0, pernae);

	pernae->instantiateNodes(1);
	pee->selfAxis    = pernae->centerAxis;
	pee->selfAxis.y =  pee->max.y;
	pernae->addNode(0, pee);
#pragma endregion

#pragma region perna direita
	coxad->selfAxis    = cintura->centerAxis;
	coxad->selfAxis.x =  coxad->centerAxis.x;
	coxad->selfAxis.y =  coxad->max.y;
	cintura->addNode(2, coxad);

	coxad->instantiateNodes(1);
	pernad->selfAxis    = pernad->centerAxis;
	pernad->selfAxis.y =  pernad->max.y;
	coxad->addNode(0, pernad);

	pernad->instantiateNodes(1);
	ped->selfAxis    = pernad->centerAxis;
	ped->selfAxis.y =  ped->max.y;
	pernad->addNode(0, ped);
#pragma endregion

#pragma region braco esquerdo
	bracoe->instantiateNodes(1);
	bracoe->selfAxis    = bracoe->centerAxis;
	bracoe->selfAxis.x =  bracoe->max.x;
	peito->addNode(1, bracoe);

	antee->instantiateNodes(1);
	antee->selfAxis = antee->centerAxis;
	antee->selfAxis.x = antee->max.x;
	bracoe->addNode(0, antee);

	maoe->selfAxis = maoe->centerAxis;
	maoe->selfAxis.x = maoe->max.x;
	antee->addNode(0, maoe);
#pragma endregion

#pragma region braco direito
	bracod->instantiateNodes(1);
	bracod->selfAxis    = bracod->centerAxis;
	bracod->selfAxis.x =  bracod->min.x;
	peito->addNode(2, bracod);

	anted->instantiateNodes(1);
	anted->selfAxis = anted->centerAxis;
	anted->selfAxis.x = anted->min.x;
	bracod->addNode(0, anted);

	maod->selfAxis = maod->centerAxis;
	maod->selfAxis.x = maod->min.x;
	anted->addNode(0, maod);
#pragma endregion

#pragma region preparando posicao inicial
	bracoe->rotate(*EDPoint::Z,  80.0f);
	bracoe->rotate(*EDPoint::X,  30.0f);
	maoe->rotate(*EDPoint::Z,    30.0f);

	bracod->rotate(*EDPoint::Z, -80.0f);
	bracod->rotate(*EDPoint::X,  30.0f);
	maod->rotate(*EDPoint::Z,   -30.0f);

	coxae->rotate(*EDPoint::Z,  -10.0f);
	pernae->rotate(*EDPoint::Z,  10.0f);
	coxad->rotate(*EDPoint::Z,   10.0f);
	pernad->rotate(*EDPoint::Z, -10.0f);
#pragma endregion

	luxor->intCounter = 0; 
	luxor->floatCounter = 0.0f;

	//luxor->setCallUpdate(trinityAnimation);
	luxor->setCallUpdate(neoAnimation);
	scenario->objects.push_back(luxor);
}

NeoMatrixScene::~NeoMatrixScene(void)
{ }