#include "cannonsScene.h"

void floatingOnY(float elapsedTime, GObject* object)
{
	object->floatCounter += elapsedTime*0.25f;
	object->position->y = sin(object->floatCounter);
}

void mru(float elapsedTime, GObject* object)
{
	if(object->intCounter == 0)
	{
		object->intCounter = 1;
	}

	object->position->x += object->intCounter*elapsedTime;
	if(object->position->x >= 10.0f)
	{
		object->intCounter = -1;
	}
	else if(object->position->x <= -10.0f)
	{
		object->intCounter = 1;
	}

	//s = s0 + v0t + at^2/2
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

	GPlane* ballPlane = new GPlane("plano3", 5.0f, 5.0f, new EDPoint(-10.0f, 2.0f, -1.0f), new EDPlane());
	GLfloat ambientMaterial2[] = {.2f, .4f, .6f, 1.0f};
	GLfloat diffuseMaterial2[] = {1.f, 1.f, 1.f, 1.0f};
	ballPlane->params = new float[4];
	ballPlane->params[0] = ballPlane->position->y;
	ballPlane->setMaterial(ambientMaterial2, diffuseMaterial2);
	ballPlane->setCallUpdate(mru);

	scenario->objects.push_back(ballPlane);
}

CannonsScene::~CannonsScene(void)
{ }