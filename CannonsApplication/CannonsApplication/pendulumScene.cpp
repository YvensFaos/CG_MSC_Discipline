#include "pendulumScene.h"

#include "edgroupedmesh.h"

void normalPendulum(float elapsedTime, GObject* object)
{
	EDGroupedMesh* pendulum = (EDGroupedMesh*)object;
	EDMesh* ball = pendulum->getGroup("Ball");
	EDMesh* chain = pendulum->getGroup("Chain");

	float omega = (10.f / 3.f) * 0.5f;
	float beta = 1.f;
	float k = pendulum->floatCounter;
	float t = ball->floatCounter;
	float teta = chain->floatCounter;

	printf("%f \n", teta);
	//Desfazendo a rotação inicial
	chain->rotate(*EDPoint::Z, -teta);

	teta = k*cos(omega*t + beta);
	//Realizando a rotação
	chain->rotate(*EDPoint::Z, teta);

	ball->floatCounter += 0.01f;
	chain->floatCounter = teta;
}

void normalCameraPendulum(float elapsedTime, EDCamera* self)
{

}

PendulumScene::PendulumScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.3f, 5.85f, 15.38f), new EDPoint(0.3f, 4.85f, 10.38f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "pendulum.txt";

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
	g = (20/255.f);
	b = (20/255.f);
	GLfloat ambientMaterial2[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (20/255.f);
	b = (20/255.f);
	GLfloat diffuseMaterial2[] = {r, g, b, 1.0f};
	chain->setMaterial(ambientMaterial2, diffuseMaterial2);

	EDMesh* ball = pendulum->getGroup("Ball");
	r = (20/255.f);
	g = (77/255.f);
	b = (20/255.f);
	GLfloat ambientMaterial3[] = {r, g, b, 1.0f};
	r = (20/255.f);
	g = (90/255.f);
	b = (20/255.f);
	GLfloat diffuseMaterial3[] = {r, g, b, 1.0f};
	ball->setMaterial(ambientMaterial3, diffuseMaterial3);

	chain->instantiateNodes(1);
	chain->addNode(0, pendulum->getGroup("Ball"));
	chain->selfAxis = chain->centerAxis;
	chain->selfAxis.y += chain->height / 2.f;
	chain->moveAxis = chain->centerAxis;
	chain->moveAxis.y += chain->height / 2.f;

	pendulum->setCallUpdate(normalPendulum);
	float initialK = 25.f;
	pendulum->floatCounter = initialK;

	float teta = 25.f;
	chain->floatCounter = teta;
	chain->rotate(*EDPoint::Z, teta);

	float initialT = 0.0f;
	ball->floatCounter = initialT;

	camera->setCallUpdate(normalCameraPendulum);
	scenario->objects.push_back(pendulum);
}

PendulumScene::~PendulumScene(void)
{ }