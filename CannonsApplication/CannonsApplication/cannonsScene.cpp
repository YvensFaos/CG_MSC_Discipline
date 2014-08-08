#include "cannonsScene.h"

CannonsScene::CannonsScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(20.0f, 33.0f, -20.0f), new EDPoint(20.0f, 20.0f, -5.0f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();
	scenario->objects.push_back(new GPlane("plano", 40.0f, 40.0f, new EDPoint(0.0f, -3.0f, -1.0f), new EDPlane()));
}

CannonsScene::~CannonsScene(void)
{ }