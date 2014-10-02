#include "loadObjScene.h"

#include "edmesh.h"

LoadObjScene::LoadObjScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(2.6f, 5.0f, 8.1f), new EDPoint(0.9f, 2.2f, 3.4f), 0.05f, 300.0f, 45.0f);

	scenario = new Scenario();

	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "table3.txt";
	char* filename2 = "luxor3.txt";
	char* filename3 = "ball.txt";

	EDMesh* table = new EDMesh("table", path, filename1);
	GLfloat ambientMaterial1[] = {.35f, .35f, .35f, 1.0f};
	GLfloat diffuseMaterial1[] = {.35f, .35f, .35f, 1.0f};
	table->setMaterial(ambientMaterial1, diffuseMaterial1);
	scenario->objects.push_back(table);

	EDMesh* ball = new EDMesh("ball", path, filename3);
	GLfloat ambientMaterial2[] = {.8f, .15f, .15f, 1.0f};
	GLfloat diffuseMaterial2[] = {.6f, .20f, .20f, 1.0f};
	ball->setMaterial(ambientMaterial2, diffuseMaterial2);
	ball->scale(EDPoint(1.f,1.f,1.f), 0.9f);
	ball->rotate(EDPoint(0.f,1.f,0.f), 60);
	ball->translate(EDPoint(2.f,1.25f,2.f));
	scenario->objects.push_back(ball);

	EDMesh* luxor = new EDMesh("luxor", path, filename2);
	GLfloat ambientMaterial3[] = {.15f, .15f, .15f, 1.0f};
	GLfloat diffuseMaterial3[] = {.20f, .20f, .20f, 1.0f};
	luxor->setMaterial(ambientMaterial3, diffuseMaterial3);
	luxor->scale(EDPoint(1.f,1.f,1.f), 0.9f);
	luxor->rotate(EDPoint(0.f,1.f,0.f), 60);
	luxor->translate(EDPoint(0.f,0.32f,0.f));
	scenario->objects.push_back(luxor);
}

LoadObjScene::~LoadObjScene(void)
{ }