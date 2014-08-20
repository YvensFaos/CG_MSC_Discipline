#include "kickingScene.h"

#include "specialObjects.h"
#include <math.h>

void cubeMovement(float elapsedTime, GObject* object)
{
	GCube* cube = (GCube*)object;
	object->floatCounter += (elapsedTime*0.05);
	
	float factor = abs(40.0f*sin(object->floatCounter) + 0.1f);

	cube->translate(new EDPoint(0.0f, -cube->points[GCube::LBN].y, 0.0f));
	cube->translate(new EDPoint(0.0f, factor, 0.0f));

	if(cube->points[GCube::LTN].y <= 20.0)
	{
		float factor2 = (cube->points[GCube::LTN].y*-0.025126f + 2.502513f);
		cube->setSize(new EDPoint(1.0f, 0.0f, 1.0f), factor2);
	}
}

KickingScene::KickingScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(40.0f, 34.2f, 90.0f), new EDPoint(40.0f, 30.0f, 75.0f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();
	GPlane* terrain = new GPlane("plano1", 20.0f, 90.0f, new EDPoint(-5.0f, 0.0f, -1.0f), new EDPlane());
	GLfloat ambientMaterial[] = {.2f, .8f, .1f, 0.9f};
	GLfloat diffuseMaterial[] = {.1f, .0f, .4f, 0.4f};
	terrain->setMaterial(ambientMaterial, diffuseMaterial);
	scenario->objects.push_back(terrain);

	GCube* cube = new GCube("cubo1", new EDPoint(-5.0f, 0.1f, 8.f), 2.5f);
	KickingBall* kickingBall = new KickingBall("bola1", cube, 20.0f);
	GLfloat ambientMaterial1[] = {.6f, .2f, .0f, 0.5f};
	GLfloat diffuseMaterial1[] = {.6f, .1f, .3f, 0.4f};
	kickingBall->setMaterial(ambientMaterial1, diffuseMaterial1);
	scenario->objects.push_back(kickingBall);

	GCube* testCube = new GCube("testCube", new EDPoint(-5.0f, 0.1f, 3.f), 2.5f);
	testCube->setMaterial(ambientMaterial1, diffuseMaterial1);
	testCube->setCallUpdate(cubeMovement);
	//scenario->objects.push_back(testCube);
}

KickingScene::~KickingScene(void)
{ }