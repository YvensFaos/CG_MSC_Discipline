#include "pendulumScene.h"

#include "edgroupedmesh.h"

void normalPendulum(float elapsedTime, GObject* object)
{
	EDGroupedMesh* pendulum = (EDGroupedMesh*)object;
	EDMesh* ball = pendulum->getGroup("Ball");
	EDMesh* chain = pendulum->getGroup("Chain");

	float omega = (10.f / (float)chain->intCounter) * 0.5f;
	float beta = 2.f;
	float k = pendulum->floatCounter;
	float t = ball->floatCounter;
	float teta = chain->floatCounter;

	//Desfazendo a rotação inicial
	chain->rotate(*EDPoint::Z, -teta);

	teta = k*cos(omega*t + beta);
	//Realizando a rotação
	chain->rotate(*EDPoint::Z, teta);

	ball->floatCounter += 0.01f;
	chain->floatCounter = teta;
}

void normalAbsPendulum(float elapsedTime, GObject* object)
{
	EDGroupedMesh* pendulum = (EDGroupedMesh*)object;
	EDMesh* ball = pendulum->getGroup("Ball");
	EDMesh* chain = pendulum->getGroup("Chain");

	float omega = (10.f / (float)chain->intCounter) * 0.5f;
	float beta = 2.f;
	float k = pendulum->floatCounter;
	float t = ball->floatCounter;
	float teta = chain->floatCounter;

	//Desfazendo a rotação inicial
	chain->rotate(*EDPoint::Z, -teta);

	teta = k*cos(omega*t + beta);
	teta = (teta <= 0.f) ? 0.0 : teta;
	//Realizando a rotação
	chain->rotate(*EDPoint::Z, teta);

	ball->floatCounter += 0.01f;
	chain->floatCounter = teta;
}

void normalAbsPendulum2(float elapsedTime, GObject* object)
{
	EDGroupedMesh* pendulum = (EDGroupedMesh*)object;
	EDMesh* ball = pendulum->getGroup("Ball");
	EDMesh* chain = pendulum->getGroup("Chain");

	float omega = (10.f / (float)chain->intCounter) * 0.5f;
	float beta = 2.f;
	float k = pendulum->floatCounter;
	float t = ball->floatCounter;
	float teta = chain->floatCounter;

	//Desfazendo a rotação inicial
	chain->rotate(*EDPoint::Z, -teta);

	teta = k*cos(omega*t + beta);
	teta = (teta >= 0.f) ? 0.0 : teta;
	//Realizando a rotação
	chain->rotate(*EDPoint::Z, teta);

	ball->floatCounter += 0.01f;
	chain->floatCounter = teta;
}

void normalCameraPendulum(float elapsedTime, EDCamera* self)
{ }

PendulumScene::PendulumScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.3f, 5.85f, 15.38f), new EDPoint(0.3f, 4.85f, 10.38f), 0.05f, 300.0f, 45.0f);
	camera = new EDCamera(new EDPoint(0.3f, 12.05f, 15.38f), new EDPoint(0.3f, 10.45f, 10.38f), 0.05f, 300.0f, 45.0f);
	camera = new EDCamera(new EDPoint(2.4f, 12.05f, 15.38f), new EDPoint(2.4f, 10.45f, 10.38f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "pendulum.txt";

	#pragma region pendulum1
	float r, g, b;
	EDGroupedMesh* pendulum = new EDGroupedMesh("pendulum", path, filename1);
	r = (77/255.f);
	g = (78/255.f);
	b = (62/255.f);
	GLfloat ambientMaterial1[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (92/255.f);
	b = (84/255.f);
	GLfloat diffuseMaterial1[] = {r, g, b, 1.0f};
	pendulum->setMaterial(ambientMaterial1, diffuseMaterial1);
	
	EDMesh* chain = pendulum->getGroup("Chain");
	r = (77/255.f);
	g = (78/255.f);
	b = (62/255.f);
	GLfloat ambientMaterial2[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (92/255.f);
	b = (84/255.f);
	GLfloat diffuseMaterial2[] = {r, g, b, 1.0f};
	chain->setMaterial(ambientMaterial2, diffuseMaterial2);

	EDMesh* ball = pendulum->getGroup("Ball");
	r = (77/255.f);
	g = (78/255.f);
	b = (62/255.f);
	GLfloat ambientMaterial3[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (92/255.f);
	b = (84/255.f);
	GLfloat diffuseMaterial3[] = {r, g, b, 1.0f};
	ball->setMaterial(ambientMaterial3, diffuseMaterial3);

	chain->instantiateNodes(1);
	chain->addNode(0, pendulum->getGroup("Ball"));
	chain->selfAxis = chain->centerAxis;
	chain->selfAxis.y += chain->height / 2.f;
	chain->moveAxis = chain->centerAxis;
	chain->moveAxis.y += chain->height / 2.f;

	float initialK = 25.f;
	pendulum->floatCounter = initialK;

	float teta = 25.f;
	chain->floatCounter = teta;
	int length = 6.f;
	chain->intCounter = length;
	chain->rotate(*EDPoint::Z, teta);

	float initialT = 0.0f;
	ball->floatCounter = initialT;
	pendulum->setCallUpdate(normalPendulum);
	scenario->objects.push_back(pendulum);
#pragma endregion

	#pragma region pendulum2
	EDGroupedMesh* pendulum2 = new EDGroupedMesh("pendulum", path, filename1);
	pendulum2->setMaterial(ambientMaterial1, diffuseMaterial1);
	
	EDMesh* chain2 = pendulum2->getGroup("Chain");
	chain2->setMaterial(ambientMaterial2, diffuseMaterial2);

	EDMesh* ball2 = pendulum2->getGroup("Ball");
	ball2->setMaterial(ambientMaterial3, diffuseMaterial3);

	chain2->instantiateNodes(1);
	chain2->addNode(0, pendulum2->getGroup("Ball"));
	chain2->selfAxis = chain2->centerAxis;
	chain2->selfAxis.y += chain2->height / 2.f;
	chain2->moveAxis = chain2->centerAxis;
	chain2->moveAxis.y += chain2->height / 2.f;

	pendulum2->floatCounter = 25.f;

	chain2->floatCounter = teta;
	chain2->intCounter = 12.f;
	chain2->rotate(*EDPoint::Z, 205);

	ball2->floatCounter = initialT;

	pendulum2->setCallUpdate(normalPendulum);
	scenario->objects.push_back(pendulum2);
	#pragma endregion

	#pragma region array pendulum
	EDGroupedMesh** pendulums = new EDGroupedMesh*[4];
	for(int i = 0; i < 4; i++)
	{
		pendulums[i] = new EDGroupedMesh("pendulum", path, filename1);
		pendulums[i]->setMaterial(ambientMaterial1, diffuseMaterial1);

		EDMesh* chainX = pendulums[i]->getGroup("Chain");
		chainX->setMaterial(ambientMaterial2, diffuseMaterial2);

		EDMesh* ballX = pendulums[i]->getGroup("Ball");
		chainX->setMaterial(ambientMaterial3, diffuseMaterial3);

		chainX->instantiateNodes(1);
		chainX->addNode(0, pendulums[i]->getGroup("Ball"));
		chainX->selfAxis = chainX->centerAxis;
		chainX->selfAxis.y += chainX->height / 2.f;
		chainX->moveAxis = chainX->centerAxis;
		chainX->moveAxis.y += chainX->height / 2.f;

		ballX->selfAxis = chainX->centerAxis;
		ballX->selfAxis.y += chainX->height / 2.f;

		chainX->translate(EDPoint(i * 2.f, 0.f, -10.f));

		if(i == 0 || i == 3)
		{
			pendulums[i]->floatCounter = 25.f;

			chainX->floatCounter = teta;
			chainX->intCounter = 1.f;

			ballX->floatCounter = initialT;

			if(i == 0)
			{
				chainX->rotate(*EDPoint::Z, 25);
				pendulums[i]->setCallUpdate(normalAbsPendulum2);
			}
			else
			{
				chainX->rotate(*EDPoint::Z, 25);
				pendulums[i]->setCallUpdate(normalAbsPendulum);
			}
		}

		scenario->objects.push_back(pendulums[i]);
	}
	#pragma endregion

	camera->setCallUpdate(normalCameraPendulum);
}

PendulumScene::~PendulumScene(void)
{ }