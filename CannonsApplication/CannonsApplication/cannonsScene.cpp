#include "cannonsScene.h"

#include "specialObjects.h"

void floatingOnY(float elapsedTime, GObject* object)
{
	object->floatCounter += elapsedTime*0.25f;
	object->position->y = sin(object->floatCounter);
}

void mru(float elapsedTime, GObject* object)
{
	if(object->position->y >= 1.8f)
	{
		object->position->x += object->intCounter*elapsedTime;
		
		float s = 0.0f;
		s = object->params[0] + object->params[1]*object->params[2] + object->params[3]*4.0f*(object->params[2]*object->params[2]);
		object->params[2] += elapsedTime*0.05f;
		object->position->y = s;
	}
	else
	{
		object->position = new EDPoint(30.0f, 2.0f, 1.0f);
		object->params[2] = 0.0f;
	}
}

CannonsScene::CannonsScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(20.0f, 14.0f, 70.0f), new EDPoint(20.0f, 10.0f, 55.0f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();
	scenario->objects.push_back(new GPlane("plano1", 45.0f, 45.0f, new EDPoint(0.0f, -3.0f, -1.0f), new EDPlane()));

	EDPoint targets[] = {EDPoint(5.0f, -1.5f, 30.f), EDPoint(35.0f, -1.5f, 30.f), EDPoint(20.0f, -1.5f, 0.f)};
	CannonBall* cannonBall = new CannonBall("bola1", targets, 3, 2.0f);
	GLfloat ambientMaterial1[] = {.2f, .2f, .4f, 1.0f};
	GLfloat diffuseMaterial1[] = {.0f, .8f, .3f, 1.0f};
	cannonBall->setMaterial(ambientMaterial1, diffuseMaterial1);
	scenario->objects.push_back(cannonBall);

	GCube* cannon1 = new GCube("canhao1", new EDPoint(5.0f, -2.5f, 30.f), 5.0f);
	GLfloat cannonAmbientMaterial[] =  {.4f, .4f, .4f, 0.5f};
	GLfloat cannonDiffuseMaterial[] = {.8f, .8f, .8f, 0.5f};
	cannon1->setMaterial(cannonAmbientMaterial, cannonDiffuseMaterial);
	scenario->objects.push_back(cannon1);

	GCube* cannon2 = new GCube("canhao2", new EDPoint(32.5f, -2.5f, 30.f), 5.0f);
	cannon2->setMaterial(cannonAmbientMaterial, cannonDiffuseMaterial);
	scenario->objects.push_back(cannon2);

	GCube* cannon3 = new GCube("canhao3", new EDPoint(18.5f, -2.5f, 5.f), 5.0f);
	cannon3->setMaterial(cannonAmbientMaterial, cannonDiffuseMaterial);
	scenario->objects.push_back(cannon3);
}

CannonsScene::~CannonsScene(void)
{ }