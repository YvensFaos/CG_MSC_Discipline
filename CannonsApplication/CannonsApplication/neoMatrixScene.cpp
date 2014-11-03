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
	
	float factor = .75f;
	switch(neo->intCounter)
	{
	case 0:
		{
			if(neo->floatCounter < 0.62f)
			{
				//printf("Timer: %f\n", neo->floatCounter);
				cintura->rotate(*EDPoint::Y,0.25f);
				barriga->rotate(*EDPoint::Y,0.75f);
				barriga->rotate(*EDPoint::X,-0.25f);
				peito->rotate(*EDPoint::Y, 0.25f);
				peito->rotate(*EDPoint::X, -0.25f);
				cabeca->rotate(*EDPoint::Y, -1.f);

				bracod->rotate(*EDPoint::Z, 0.5f);
				bracod->rotate(*EDPoint::X, 0.5f);
				bracod->rotate(*EDPoint::Y, 0.45f);
				anted->rotate(*EDPoint::Z, 0.5f);

				bracoe->rotate(*EDPoint::Z, 1.5f);
				bracoe->rotate(*EDPoint::X, -2.5f);
			}
			else if(neo->floatCounter < 1.1f)
			{
				cintura->translate(EDPoint(0.0f, -0.01f, 0.0f));
				cintura->rotate(*EDPoint::Y,0.25f);
				barriga->rotate(*EDPoint::Y,0.25f);
				peito->rotate(*EDPoint::Y,0.25f);
				cabeca->rotate(*EDPoint::Y,-1.f);

				coxad->rotate(*EDPoint::X, -0.75f);
				coxad->rotate(*EDPoint::Y, 0.75f);
				pernad->rotate(*EDPoint::X, 1.0f);
				ped->rotate(*EDPoint::X, -.025f);

				coxae->rotate(*EDPoint::X, -1.5f);
				coxae->rotate(*EDPoint::Y, -1.5f);
				pernae->rotate(*EDPoint::X, 2.0f);
				pee->rotate(*EDPoint::X, -.025f);
				pee->rotate(*EDPoint::Z,  .25f);

				bracod->rotate(*EDPoint::Z, 0.25f);
				bracod->rotate(*EDPoint::X, 0.25f);
				bracod->rotate(*EDPoint::Y, 1.75f);
				anted->rotate(*EDPoint::Y, -.75f);
				anted->rotate(*EDPoint::X, 0.2f);

				bracoe->rotate(*EDPoint::Y, -1.75f);
				bracoe->rotate(*EDPoint::X, -1.75f);
				antee->rotate(*EDPoint::Y, 1.75f);
				maoe->rotate(*EDPoint::X, -1.75f);
			}
			else if(neo->floatCounter < 1.9f)
			{
				cintura->translate(EDPoint(0.0f, -0.02f, 0.0f));
				cintura->rotate(*EDPoint::X, -0.5f);
				barriga->rotate(*EDPoint::Y, -0.5f);
				barriga->rotate(*EDPoint::X, -0.5f);
				cabeca->rotate(*EDPoint::X, 0.5f);

				anted->rotate(*EDPoint::Z, 1.5f);

				bracoe->rotate(*EDPoint::Z, 1.5f);

				coxae->rotate(*EDPoint::X, -.5f);
				pernae->rotate(*EDPoint::X, 1.f);
				coxad->rotate(*EDPoint::X, -.5f);
				pernad->rotate(*EDPoint::X, 1.f);
			}
			else if(neo->floatCounter < 2.8f)
			{
				cintura->translate(EDPoint(0.0f, -0.01f, 0.0f));

				cabeca->rotate(*EDPoint::X, -0.5f);
				cabeca->rotate(*EDPoint::Z, 0.5f);
				cabeca->rotate(*EDPoint::Z, -0.5f);
				peito->rotate(*EDPoint::Z, 0.25f);
				barriga->rotate(*EDPoint::Z, 0.5f);

				bracoe->rotate(*EDPoint::Z, 0.75f);
				bracoe->rotate(*EDPoint::Y, 1.2f);
				bracoe->rotate(*EDPoint::X, 0.5f);

				bracod->rotate(*EDPoint::Y, 0.75f);
				bracod->rotate(*EDPoint::Z, 2.f);
				bracod->rotate(*EDPoint::X, 0.25f);
				anted->rotate(*EDPoint::Z, -1.5f);

				coxad->rotate(*EDPoint::X, -.5f);
				ped->rotate(*EDPoint::X, .5f);

				coxae->rotate(*EDPoint::Y, -.2f);
				pee->rotate(*EDPoint::X, -.4f);
				pee->rotate(*EDPoint::Z, -.4f);
			}
			else if(neo->floatCounter < 3.425f)
			{
				cintura->translate(EDPoint(0.0f, -0.01f, 0.0f));

				cabeca->rotate(*EDPoint::X, 0.5f);
				cabeca->rotate(*EDPoint::Z, 0.5f);
				peito->rotate(*EDPoint::Y, -0.1f);
				barriga->rotate(*EDPoint::Y, -0.2f);

				coxae->rotate(*EDPoint::X, -.25f);
				pee->rotate(*EDPoint::X, .6f);
				pee->rotate(*EDPoint::Z, .6f);
				pee->rotate(*EDPoint::Y, .4f);

				ped->rotate(*EDPoint::Y, -.4f);

				bracod->rotate(*EDPoint::Z, .75f);
				anted->rotate(*EDPoint::Z, .75f);
				anted->rotate(*EDPoint::Y, -.25f);
				maod->rotate(*EDPoint::X, -.5f);
				/*
				bracoe->rotate(*EDPoint::Y, 1.2f);
				bracoe->rotate(*EDPoint::X, 0.5f);

				bracod->rotate(*EDPoint::Y, 0.75f);
				bracod->rotate(*EDPoint::Z, 2.f);
				bracod->rotate(*EDPoint::X, 0.25f);
				anted->rotate(*EDPoint::Z, -1.5f);

				ped->rotate(*EDPoint::X, .5f);

				pee->rotate(*EDPoint::X, -.4f);
				pee->rotate(*EDPoint::Z, -.4f);*/
			}
			else if(neo->floatCounter < 4.0f)
			{
				coxae->rotate(*EDPoint::X, -.0f);
			}
		}
		break;
	}
}

void testCameraUpdate2(float elapsedTime, EDCamera* self)
{
	self->timer += elapsedTime;
	if(self->timer < 0.4f)
	{
		self->zoomIn();
	}
	else if(self->timer < 0.8f)
	{
		self->translateTo(new EDPoint(-0.01f, 0.0f, 0.0f));
	}
}

void testCameraUpdate3(float elapsedTime, EDCamera* self)
{
	self->timer += elapsedTime;
}

NeoMatrixScene::NeoMatrixScene(void) : Scene()
{
	//camera = new EDCamera(new EDPoint(-10.0f, -2.25f, 0.705), new EDPoint(-0.75f, -2.25f, -0.909f), 0.05f, 300.0f, 45.0f);
	camera = new EDCamera(new EDPoint(0.0f, -0.75f, -13.5), new EDPoint(0.0f, -0.75f, -4.2f), 0.05f, 300.0f, 45.0f);
	camera->intCounter = 0;
	camera->floatCounter = 0.0f;
	camera->timer = 0.0f;
	camera->setCallUpdate(testCameraUpdate2);
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