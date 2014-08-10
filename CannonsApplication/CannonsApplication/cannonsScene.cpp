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

	GPlane* movingPlane = new GPlane("plano2", 20.0f, 20.0f, new EDPoint(0.0f, 2.0f, -1.0f), new EDPlane());
	GLfloat ambientMaterial[] = {.6f, .2f, .3f, 1.0f};
	GLfloat diffuseMaterial[] = {1.f, 1.f, 1.f, 1.0f};
	movingPlane->setMaterial(ambientMaterial, diffuseMaterial);
	movingPlane->setCallUpdate(floatingOnY);

	scenario->objects.push_back(movingPlane);

	GPlane* ballPlane = new GPlane("plano3", 5.0f, 5.0f, new EDPoint(30.0f, 2.0f, 1.0f), new EDPlane());
	GLfloat ambientMaterial2[] = {.2f, .4f, .6f, 1.0f};
	GLfloat diffuseMaterial2[] = {1.f, 1.f, 1.f, 1.0f};
	ballPlane->intCounter = -1;
	ballPlane->params = new float[4];
	ballPlane->params[0] = ballPlane->position->y;
	ballPlane->params[1] = 6.0f;
	ballPlane->params[2] = 0.0f;
	ballPlane->params[3] = -1.0f;
	ballPlane->setMaterial(ambientMaterial2, diffuseMaterial2);
	ballPlane->setCallUpdate(mru);

	scenario->objects.push_back(ballPlane);

	/*GCube* cube = new GCube("cubo1", new EDPoint(30.0f, 2.1f, 10.f), new EDPoint(32.0f, 4.1f, 12.f));
	GLfloat ambientMaterial3[] = {.0f, .6f, .3f, 1.0f};
	GLfloat diffuseMaterial3[] = {.3f, .8f, .2f, 1.0f};
	cube->setMaterial(ambientMaterial3, diffuseMaterial3);

	scenario->objects.push_back(cube);*/

	EDPoint targets[] = {EDPoint(30.0f, 2.1f, 10.f), EDPoint(10.0f, 2.1f, 10.f), EDPoint(20.0f, 2.1f, 30.f), EDPoint(10.0f, 5.0f, 40.f)};
	CannonBall* cannonBall = new CannonBall("bola1", targets, 4, 2.0f);
	GLfloat ambientMaterial4[] = {.2f, .2f, .4f, 1.0f};
	GLfloat diffuseMaterial4[] = {.0f, .8f, .3f, 1.0f};
	cannonBall->setMaterial(ambientMaterial4, diffuseMaterial4);

	scenario->objects.push_back(cannonBall);
}

CannonsScene::~CannonsScene(void)
{ }