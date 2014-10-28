#include "trinityScene.h"

#include "edgroupedmesh.h"

void trinityAnimation(float elapsedTime, GObject* object)
{
	EDGroupedMesh* trinity = (EDGroupedMesh*)object;
	EDMesh* cintura = trinity->getGroup("Cintura");
	EDMesh* coxae = trinity->getGroup("Coxa.E");
	EDMesh* coxad = trinity->getGroup("Coxa.D");
	EDMesh* pernae = trinity->getGroup("Perna.E");
	EDMesh* pernad = trinity->getGroup("Perna.D");
	EDMesh* pee = trinity->getGroup("Pe.E");
	EDMesh* ped = trinity->getGroup("Pe.D");
	EDMesh* bracoe = trinity->getGroup("Braco.E");
	EDMesh* bracod = trinity->getGroup("Braco.D");
	EDMesh* antee = trinity->getGroup("Ante.E");
	EDMesh* anted = trinity->getGroup("Ante.D");
	EDMesh* maoe = trinity->getGroup("Mao.E");
	EDMesh* maod = trinity->getGroup("Mao.D");
	EDMesh* barriga = trinity->getGroup("Barriga");
	EDMesh* peito = trinity->getGroup("Peito");
	EDMesh* cabeca = trinity->getGroup("Cabeca");

	switch(trinity->intCounter)
	{
	case 0:
		{
			//Levantando os braços
			if(trinity->floatCounter < 70.0)
			{
				float factor = 0.25;
				trinity->floatCounter += .25f;
				bracoe->rotate(*EDPoint::Z,-factor);
				antee->rotate(*EDPoint::Z, -factor/5.f);

				bracod->rotate(*EDPoint::Z, factor);
				bracod->rotate(*EDPoint::Z, factor/5.f);

				cabeca->rotate(*EDPoint::X, factor/3.f);
				cintura->rotate(*EDPoint::X, factor/10.f);
				pernae->rotate(*EDPoint::X, -factor/5.f);
				pernad->rotate(*EDPoint::X, -factor/5.f);

				peito->rotate(*EDPoint::X, -factor/10.f);

				pee->rotate(*EDPoint::X, factor/7.f);
				ped->rotate(*EDPoint::X, factor/7.f);
				
				cintura->translate(EDPoint(0.0f, 0.00125f, 0.0f));
			}
			else
			{
				trinity->intCounter++;
				trinity->floatCounter = 0.0;
			}
		}
		break;
	case 1:
		{
			//Posicionando os braços e mãos
			if(trinity->floatCounter < 30.0)
			{
				float factor = 0.25;
				trinity->floatCounter += .25f;
				bracoe->rotate(*EDPoint::Y, factor/1.5f);
				antee->rotate(*EDPoint::Y, -factor*2.f);
				maoe->rotate(*EDPoint::Z,  -factor*3.f);

				bracod->rotate(*EDPoint::Y, -factor/1.5f);
				anted->rotate(*EDPoint::Y,   factor*2.f);
				maod->rotate(*EDPoint::X,    factor*4.f);

				cabeca->rotate(*EDPoint::X, -factor/4.f);
				cintura->rotate(*EDPoint::X, factor/5.f);

				coxae->rotate(*EDPoint::Y, -factor*1.5f);
				coxad->rotate(*EDPoint::Y,  factor*1.5f);

				coxae->rotate(*EDPoint::X, -factor*3.5f);
				coxad->rotate(*EDPoint::X, -factor*3.5f);

				pernae->rotate(*EDPoint::X, factor*3.5f);
				pernad->rotate(*EDPoint::X, factor*3.5f);

				pernae->rotate(*EDPoint::Y, factor*1.5f);
				pernad->rotate(*EDPoint::Y, -factor*1.5f);

				pee->rotate(*EDPoint::X, factor*2.f);
				ped->rotate(*EDPoint::X, factor*2.f);

				peito->rotate(*EDPoint::X, -factor/2.f);

				cintura->translate(EDPoint(0.0f, 0.0025f, 0.0f));
			}
			else
			{
				trinity->intCounter++;
				trinity->floatCounter = 0.0;
			}
		}
		break;
		case 2:
		{
			//Posicionando os braços e mãos
			if(trinity->floatCounter < 30.0)
			{
				float factor = 0.25;
				trinity->floatCounter += .25f;
				bracoe->rotate(*EDPoint::Y, factor/1.2f);
				bracod->rotate(*EDPoint::Y, factor/1.5f);
				bracoe->rotate(*EDPoint::Z, -factor/1.25f);
				antee->rotate(*EDPoint::Z, factor*0.75);
				maod->rotate(*EDPoint::Y, -factor*2.5f);

				coxad->rotate(*EDPoint::X, -factor*0.6f);
				coxad->rotate(*EDPoint::Y,  factor*0.8f);
				pernad->rotate(*EDPoint::Z, -factor*1.5f);
				ped->rotate(*EDPoint::X, -factor*1.5f);
				ped->rotate(*EDPoint::Z, factor*1.5f);

				coxae->rotate(*EDPoint::X, -factor*0.8f);
				coxae->rotate(*EDPoint::Y,  factor*0.6f);
				pernae->rotate(*EDPoint::X,  factor*0.8f);
				pernae->rotate(*EDPoint::Y,  factor*0.4f);
				pernae->rotate(*EDPoint::Z,  factor*1.2f);
				pee->rotate(*EDPoint::Z,  -factor*0.4f);
				pee->rotate(*EDPoint::Y,  -factor*1.2f);

				cintura->translate(EDPoint(0.0f, 0.0025f, 0.0f));
				cabeca->rotate(*EDPoint::X, factor/4.f);
			}
			else
			{
				trinity->intCounter++;
				trinity->floatCounter = 0.0;
			}
		}
		break;
	}
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
	//Lateral perto
	//camera = new EDCamera(new EDPoint(-7.78f, 0.34f, 0.76f), new EDPoint(-2.87f, -0.65f, -0.9f), 0.05f, 300.0f, 45.0f);
	
	//Lateral
	//camera = new EDCamera(new EDPoint(-11.87f, 1.16f, 2.14f), new EDPoint(-6.96f, 0.17f, 0.48f), 0.05f, 300.0f, 45.0f);

	//3 4
	//camera = new EDCamera(new EDPoint(-6.41f, 1.74f, 9.14f), new EDPoint(-3.61f, 0.75f, 4.72f), 0.05f, 300.0f, 45.0f);

	//Frontal
	//camera = new EDCamera(new EDPoint(-0.37f, 2.07f, 12.47f), new EDPoint(-0.15f, 1.08f, 7.24f), 0.05f, 300.0f, 45.0f);

	//Lateral perto 2
	//camera = new EDCamera(new EDPoint(-3.90f, 1.67f, 5.97f), new EDPoint(-0.37f, 0.68f, 2.11f), 0.05f, 300.0f, 45.0f);
	
	//Camera para ver as pernas
	//camera = new EDCamera(new EDPoint(4.90f, 1.53f, 4.91f), new EDPoint(1.04f, 0.54f, 1.38f), 0.05f, 300.0f, 45.0f);
	
	//Camera para ver as pernas 2
	camera = new EDCamera(new EDPoint(1.44f, 1.67f, 7.16f), new EDPoint(0.75f, 0.68f, 1.97f), 0.05f, 300.0f, 45.0f);
	
	//camera = new EDCamera(new EDPoint(4.20f, 2.55f, 16.63f), new EDPoint(1.78f, 1.56f, 11.99f), 0.05f, 300.0f, 45.0f);
	//camera = new EDCamera(new EDPoint(-0.28f, 12.49f, 2.78f), new EDPoint(-0.97f, -1.29f, -2.4f), 0.05f, 300.0f, 45.0f);

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
	
#pragma region carregando pedaços do modelo
	EDMesh* cintura = luxor->getGroup("Cintura");
	cintura->visible = true;
	EDMesh* coxae = luxor->getGroup("Coxa.E");
	coxae->visible = true;
	EDMesh* coxad = luxor->getGroup("Coxa.D");
	coxad->visible = true;
	EDMesh* pernae = luxor->getGroup("Perna.E");
	pernae->visible = true;
	EDMesh* pernad = luxor->getGroup("Perna.D");
	pernad->visible = true;
	EDMesh* pee = luxor->getGroup("Pe.E");
	pee->visible = true;
	EDMesh* ped = luxor->getGroup("Pe.D");
	ped->visible = true;

	EDMesh* bracoe = luxor->getGroup("Braco.E");
	bracoe->visible = true;
	EDMesh* bracod = luxor->getGroup("Braco.D");
	bracod->visible = true;
	EDMesh* antee = luxor->getGroup("Ante.E");
	antee->visible = true;
	EDMesh* anted = luxor->getGroup("Ante.D");
	anted->visible = true;
	EDMesh* maoe = luxor->getGroup("Mao.E");
	maoe->visible = true;
	EDMesh* maod = luxor->getGroup("Mao.D");
	maod->visible = true;

	EDMesh* barriga = luxor->getGroup("Barriga");
	barriga->visible = true;
	EDMesh* peito = luxor->getGroup("Peito");
	peito->visible = true;
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

	//cintura->setCallUpdate(testMethodRotationBaby);
	//bracoe->setCallUpdate(testMethodRotationBaby);
	//bracod->setCallUpdate(testMethodRotationBaby);

#pragma region preparando posicao inicial
	bracoe->rotate(*EDPoint::Z,  80.0f);
	bracoe->rotate(*EDPoint::X,  30.0f);
	antee->rotate(*EDPoint::X,  -80.0f);
	antee->rotate(*EDPoint::Z,   10.0f);
	maoe->rotate(*EDPoint::Z,    30.0f);

	bracod->rotate(*EDPoint::Z, -80.0f);
	bracod->rotate(*EDPoint::X,  30.0f);
	anted->rotate(*EDPoint::X,  -80.0f);
	anted->rotate(*EDPoint::Z,  -10.0f);
	maod->rotate(*EDPoint::Z,   -30.0f);
#pragma endregion

	luxor->intCounter = 0; 
	luxor->floatCounter = 0;
	luxor->setCallUpdate(trinityAnimation);
	scenario->objects.push_back(luxor);
}

TrinityScene::~TrinityScene(void)
{ }