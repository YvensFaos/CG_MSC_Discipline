#include "trinityScene.h"

#include "edgroupedmesh.h"

void trinityAnimation2(float elapsedTime, GObject* object)
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

	trinity->floatCounter += elapsedTime;
	if(trinity->floatCounter < 3.6f)
	{
		float factor = .75f;
		switch(trinity->intCounter)
		{
		case 0:
			{
				if(bracoe->rotation.z > -10.0)
				{
					bracoe->rotate(*EDPoint::Z,-factor);
					antee->rotate(*EDPoint::Z, -factor/5.f);
					maoe->rotate(*EDPoint::Z, 0.001);

					bracod->rotate(*EDPoint::Z, factor);
					anted->rotate(*EDPoint::Z, factor/5.f);
					maod->rotate(*EDPoint::Z, 0.001);

					coxae->rotate(*EDPoint::Y, -0.5f);
					coxad->rotate(*EDPoint::Y,  0.5f);

					coxae->rotate(*EDPoint::X, -0.5f);
					coxad->rotate(*EDPoint::X, -0.5f);
					pernae->rotate(*EDPoint::X, 1.f);
					pernad->rotate(*EDPoint::X, 1.0f);
				}
				else
				{
					trinity->intCounter++;
					bracoe->rotate(*EDPoint::Y, .5f);
					antee->rotate(*EDPoint::Y, -1.f);
					bracoe->rotate(*EDPoint::X, .25f);
					antee->rotate(*EDPoint::X, -.5f);
					maoe->rotate(*EDPoint::Z, -.95f);

					bracod->rotate(*EDPoint::Y, -.5f);
					anted->rotate(*EDPoint::Y, 1.f);
					bracod->rotate(*EDPoint::X, .25f);
					anted->rotate(*EDPoint::X, -.5f);
					maod->rotate(*EDPoint::Z, 1.5f);
				}
				peito->rotate(*EDPoint::X, .125f);
				cabeca->rotate(*EDPoint::X, .125f);
				cintura->translate(EDPoint(0.0f,0.005f, 0.0f));
			}
			break;
		case 1:
			{
				if(bracoe->rotation.y < 30.0)
				{
					bracoe->rotate(*EDPoint::Y, .5f);
					antee->rotate(*EDPoint::Y, -1.f);
					bracoe->rotate(*EDPoint::X, .25f);
					antee->rotate(*EDPoint::X, -.5f);
					maoe->rotate(*EDPoint::Z, -.95f);

					bracod->rotate(*EDPoint::Y, -.5f);
					anted->rotate(*EDPoint::Y, 1.f);
					bracod->rotate(*EDPoint::X, .25f);
					anted->rotate(*EDPoint::X, -.5f);
					maod->rotate(*EDPoint::Z, 1.5f);

					coxae->rotate(*EDPoint::Y,  0.5f);
					coxad->rotate(*EDPoint::Y, -0.02f);

					coxae->rotate(*EDPoint::X, -0.95f);
					coxad->rotate(*EDPoint::X, -0.65f);

					pee->rotate(*EDPoint::X,  0.80f);
					pee->rotate(*EDPoint::Z,  0.80f);
					ped->rotate(*EDPoint::X,  0.80f);
					ped->rotate(*EDPoint::Z, -0.80f);
				}
				else
				{
					trinity->intCounter++;
				}
				peito->rotate(*EDPoint::X, -.125f);
				cabeca->rotate(*EDPoint::X, -.125f);
				cintura->translate(EDPoint(0.0f,0.005f, 0.0f));
			}
			break;
		}
	}
	else
	{
		//Hora do chute!
		switch(trinity->intCounter)
		{
		case 2:
			{
				if(coxae->rotation.x < -90.f)
				{
					coxae->rotate(*EDPoint::X,  1.5f);
					pernae->rotate(*EDPoint::Z,-1.0f);
					pernae->rotate(*EDPoint::X,-6.0f);
					pee->rotate(*EDPoint::X,    1.0f);
					coxad->rotate(*EDPoint::Z,-1.0f);

					barriga->rotate(*EDPoint::X, 0.5f);
					bracod->rotate(*EDPoint::Y, 0.5f);
					bracoe->rotate(*EDPoint::Y,-0.5f);
				}
			}
			break;
		}
	}
}

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
				float factor = 1.f;
				trinity->floatCounter += 1.f;
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
				float factor = .5f;
				trinity->floatCounter += .5f;
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

				cintura->translate(EDPoint(0.0f, 0.005f, 0.0f));
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
				float factor = 0.5f;
				trinity->floatCounter += 0.5f;
				bracoe->rotate(*EDPoint::Y, factor/1.2f);
				bracod->rotate(*EDPoint::Y, factor/1.5f);
				bracoe->rotate(*EDPoint::Z, -factor/1.25f);
				antee->rotate(*EDPoint::Z, factor*0.75);
				maod->rotate(*EDPoint::Y, -factor*2.5f);

				coxad->rotate(*EDPoint::X, -factor*0.4f);
				coxad->rotate(*EDPoint::Y,  factor*0.8f);
				pernad->rotate(*EDPoint::Z, -factor*0.5f);
				ped->rotate(*EDPoint::X, factor*0.5f);
				
				coxae->rotate(*EDPoint::X, -factor*0.4f);
				coxae->rotate(*EDPoint::Y,  factor*0.6f);
				pernae->rotate(*EDPoint::Z,  factor*1.2f);
				pee->rotate(*EDPoint::Z,  -factor*0.4f);
				pee->rotate(*EDPoint::Y,  -factor*1.2f);
				

				cabeca->rotate(*EDPoint::X, factor/4.f);

				cintura->translate(EDPoint(0.0f, 0.005f, 0.0f));
			}
			else
			{
				trinity->intCounter++;
				trinity->floatCounter = 0.0;
			}
		}
		break;
		case 3:
		{
			//Tempo da câmera rodar
			if(trinity->floatCounter < 30.0)
			{
				float factor = 0.5f;
				trinity->floatCounter += 0.5f;
				bracoe->rotate(*EDPoint::Y, factor/1.2f);
				bracod->rotate(*EDPoint::Y, factor/1.2f);

				coxae->rotate(*EDPoint::X,  -factor*0.2f);
				coxae->rotate(*EDPoint::Z,  -factor*1.2f);

				coxad->rotate(*EDPoint::X,  -factor*0.2f);
				pernad->rotate(*EDPoint::X,  -factor*0.2f);
				ped->rotate(*EDPoint::X,  -factor*0.2f);
				if(pee->rotation.z > 0.0f)
				{
					pee->rotate(*EDPoint::Z,    -0.195833f/8.f);
				}
				else
				{
					pee->rotate(*EDPoint::Z, -pee->rotation.z);
				}
			}
			else
			{
				trinity->intCounter++;
				trinity->floatCounter = 0.0;
			}
		}
		break;
		case 4:
		{
			//Chute
			float factor = 0.25;

			if(coxae->rotation.x < -90.0f)
			{
				coxae->rotate(*EDPoint::X,  factor*2.f);
				pernae->intCounter = 0;
			}
			else if(pernae->intCounter == 0)
			{
				pernae->rotate(*EDPoint::Y,  18.f);
				pernae->intCounter++;
			}
			else if(pernae->rotation.x > -90.0f)
			{
				pernae->rotate(*EDPoint::X,  -factor*4.f);
			}
			else
			{
				trinity->intCounter++;
			}

			coxad->rotate(*EDPoint::X,   factor*1.1f);
			cabeca->rotate(*EDPoint::X, -factor*1.2f);
			peito->rotate(*EDPoint::X,   factor*1.2f);
			bracod->rotate(*EDPoint::X, -factor*2.4f);
			anted->rotate(*EDPoint::X,  -factor*2.4f);
			maod->rotate(*EDPoint::X,   -factor*1.2f);
			bracoe->rotate(*EDPoint::X,  factor*1.2f);
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

void testCameraUpdate1(float elapsedTime, EDCamera* self)
{
	self->timer += elapsedTime;
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
	}

	
}

TrinityScene::TrinityScene(void) : Scene()
{
#pragma region cameras
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
	//camera = new EDCamera(new EDPoint(1.44f, 1.67f, 7.16f), new EDPoint(0.75f, 0.68f, 1.97f), 0.05f, 300.0f, 45.0f);
	
	//Camera para ver as pernas 3
	//camera = new EDCamera(new EDPoint(5.43f, 1.91f, 4.92f), new EDPoint(1.56f, 0.92f, 1.39f), 0.05f, 300.0f, 45.0f);

	//Distante
	//camera = new EDCamera(new EDPoint(4.20f, 2.55f, 16.63f), new EDPoint(1.78f, 1.56f, 11.99f), 0.05f, 300.0f, 45.0f);

	//Superior
	//camera = new EDCamera(new EDPoint(-0.28f, 12.49f, 2.78f), new EDPoint(-0.97f, -1.29f, -2.4f), 0.05f, 300.0f, 45.0f);
	
	//Lateral superior
	//camera = new EDCamera(new EDPoint(-7.56f, 2.78f, 9.10f), new EDPoint(-4.03f, 1.79f, 5.24f), 0.05f, 300.0f, 45.0f);

	//Novo frontal
#pragma endregion
	//0.0f, -0.752869487, -0.153204992
	camera = new EDCamera(new EDPoint(0.0f, -0.75f, 9.15), new EDPoint(0.0f, -0.75f, -0.15f), 0.05f, 300.0f, 45.0f);
	camera->intCounter = 0;
	camera->floatCounter = 0.0f;
	camera->timer = 0.0f;
	camera->setCallUpdate(testCameraUpdate1);
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
	luxor->floatCounter = 0.0f;

	//luxor->setCallUpdate(trinityAnimation);
	luxor->setCallUpdate(trinityAnimation2);
	scenario->objects.push_back(luxor);
}

TrinityScene::~TrinityScene(void)
{ }