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
	camera = new EDCamera(new EDPoint(20.0f, 33.0f, -20.0f), new EDPoint(20.0f, 20.0f, -5.0f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();
	scenario->objects.push_back(new GPlane("plano1", 40.0f, 40.0f, new EDPoint(0.0f, -3.0f, -1.0f), new EDPlane()));

	EDPoint targets[] = {EDPoint(35.0f, 2.f, 0.f), EDPoint(5.0f, 2.f, 0.f), EDPoint(20.0f, 2.f, 30.f)};
	CannonBall* cannonBall = new CannonBall("bola1", targets, 3, 2.0f);
	GLfloat ambientMaterial4[] = {.2f, .2f, .4f, 1.0f};
	GLfloat diffuseMaterial4[] = {.0f, .8f, .3f, 1.0f};
	cannonBall->setMaterial(ambientMaterial4, diffuseMaterial4);

	scenario->objects.push_back(cannonBall);
}

CannonsScene::~CannonsScene(void)
{ }