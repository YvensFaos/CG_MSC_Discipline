#include "transformScene.h"

#include "specialObjects.h"

void scaleOnXYZ(float elapsedTime, GObject* object)
{
	GCube* cube = (GCube*)object;
	object->floatCounter += (elapsedTime*0.5);
	
	float factor = 1.0005f; //0.5f + sin(object->floatCounter);

	printf("scale factor: %f\n", factor);
	cube->scale(new EDPoint(1.0f, 1.0f, 1.0f), factor);
}

void translateOnXYZ(float elapsedTime, GObject* object)
{
	GCube* cube = (GCube*)object;
	object->floatCounter += (elapsedTime*0.5);
	
	float factor = 0.05f; //0.5f + sin(object->floatCounter);

	printf("translate factor: %f\n", factor);
	cube->translate(new EDPoint(factor, factor, factor));
}

void rotateOnXYZ(float elapsedTime, GObject* object)
{
	GCube* cube = (GCube*)object;
	object->floatCounter += (elapsedTime*0.5);
	
	float factor = 2.f; //0.5f + sin(object->floatCounter);

	printf("rotate factor: %f\n", factor);
	cube->rotate(new EDPoint(0.0f, 1.0f, 0.0f), factor);
}

TransformScene::TransformScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(20.0f, 14.0f, 70.0f), new EDPoint(20.0f, 10.0f, 55.0f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();
	GPlane* terrain = new GPlane("plano1", 37.5f, 45.0f, new EDPoint(0.0f, -3.0f, -1.0f), new EDPlane());
	GLfloat ambientMaterial[] = {.2f, .8f, .1f, 0.9f};
	GLfloat diffuseMaterial[] = {.1f, .0f, .4f, 0.4f};
	terrain->setMaterial(ambientMaterial, diffuseMaterial);
	scenario->objects.push_back(terrain);

	GCube* cube = new GCube("cubo1", new EDPoint(20.0f, -1.5f, 30.f), 2.5f);
	GLfloat ambientMaterial1[] = {.6f, .2f, .0f, 0.5f};
	GLfloat diffuseMaterial1[] = {.6f, .1f, .3f, 0.4f};
	cube->setMaterial(ambientMaterial1, diffuseMaterial1);
	cube->setCallUpdate(rotateOnXYZ);
	cube->floatCounter = 0.0f;
	scenario->objects.push_back(cube);
}

TransformScene::~TransformScene(void)
{ }