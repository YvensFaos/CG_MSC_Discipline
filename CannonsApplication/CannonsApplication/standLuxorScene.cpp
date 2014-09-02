#include "standLuxorScene.h"

#include "edmesh.h"

float squashTime = 0.225f;
float squash = 1.0002f;
float strech = 0.9998f;
float translatePos = -0.0004f;

void kickingBall(float elapsedTime, GObject* object)
{
	EDMesh* ball = (EDMesh*)object;
	int state = ball->params[3];
	switch(state)
	{
		case 0:
			{
				ball->params[2] += (elapsedTime*0.5);
	
				float y = ball->params[0] + ball->params[1]*ball->params[2] - 0.2f*(ball->params[2]*ball->params[2]);
				ball->translate(EDPoint(0.0f, -ball->min.y, 0.0f));
				ball->translate(EDPoint(0.0f, y, 0.0f));

				if(y < ball->params[0])
				{
					ball->params[3] = 1;
					ball->params[2] = 0;

					ball->translate(EDPoint(0.0f, -y, 0.0f));
					ball->translate(EDPoint(0.0f, ball->params[0], 0.0f));
				}
			}
			break;
		case 1:
			{
				//Squash!
				if(ball->params[2] < squashTime)
				{
					ball->params[2] += 0.005;
					ball->scale(EDPoint(0.0f, 1.0f, 0.0f),  strech);
					ball->scale(EDPoint(1.0f, 0.0f, 1.0f),  squash);
					ball->translate(EDPoint(-translatePos, 0.0f, -translatePos));
				}
				else
				{
					ball->params[2] = 0;
					ball->params[3] = 2;
				}
			}
			break;
		case 2:
			{
				//Squash!
				if(ball->params[2] < squashTime/2.f)
				{
					ball->params[2] += 0.005;
					ball->scale(EDPoint(0.0f, 1.0f, 0.0f), squash + 0.0002f);
					ball->scale(EDPoint(1.0f, 0.0f, 1.0f), strech - 0.0002f);
					ball->translate(EDPoint(translatePos, 0.0f,  translatePos));
				}
				else
				{
					ball->params[2] = 0;
					ball->params[3] = 0;
				}
			}
			break;
	}	
}

StandLuxorScene::StandLuxorScene(void) : Scene()
{
	camera = new EDCamera(new EDPoint(0.4f, 1.7f, 6.f), new EDPoint(0.41f, 1.1f, 1.f), 0.05f, 300.0f, 45.0f);

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

	ball->setCallUpdate(kickingBall);
	ball->params = new float[4];
	ball->params[0] = ball->min.y;
	ball->params[1] = 1.5f;
	ball->params[2] = 0.0f;
	ball->params[3] = 0.0f;

	EDMesh* luxor = new EDMesh("luxor", path, filename2);
	GLfloat ambientMaterial3[] = {.15f, .15f, .15f, 1.0f};
	GLfloat diffuseMaterial3[] = {.20f, .20f, .20f, 1.0f};
	luxor->setMaterial(ambientMaterial3, diffuseMaterial3);
	luxor->scale(EDPoint(1.f,1.f,1.f), 0.9f);
	luxor->rotate(EDPoint(0.f,1.f,0.f), 60);
	luxor->translate(EDPoint(-.9f,0.32f,0.f));
	luxor->updateMinValue();
	scenario->objects.push_back(luxor);
}

StandLuxorScene::~StandLuxorScene(void)
{ }