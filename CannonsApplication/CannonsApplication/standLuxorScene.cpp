#include "standLuxorScene.h"

#include "edmesh.h"

float squashTime = 0.225f;
float squash = 1.0002f;
float strech = 0.9998f;
float translatePos = -0.0004f;

#define NORMAL_CAMERA
#define BIRDS_EYES
#define WORMS_EYES

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
#ifdef NORMAL_CAMERA
	camera = new EDCamera(new EDPoint(0.4f, 2.5f, 6.59f), new EDPoint(0.41f, 1.5f, 1.6f), 0.05f, 300.0f, 45.0f);
#endif
#ifdef BIRDS_EYES
	camera = new EDCamera(new EDPoint(0.4f, 2.5f, 6.59f), new EDPoint(0.41f, 1.5f, 1.6f), 0.05f, 300.0f, 45.0f);
#endif
#ifdef WORMS_EYES
	camera = new EDCamera(new EDPoint(-1.7f, 0.4f, 1.79f), new EDPoint(2.12f, 4.4f, -1.4f), 0.05f, 300.0f, 90.0f);
#endif

	scenario = new Scenario();

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "table3.txt";
	char* filename2 = "luxor_203.txt";
	char* filename3 = "ball.txt";

	EDMesh* table = new EDMesh("table", path, filename1);
	float r = (58/255.f);
	float g = (59/255.f);
	float b = (54/255.f);
	GLfloat ambientMaterial1[] = {r, g, b, 1.0f};
	r = (90/255.f);
	g = (92/255.f);
	b = (84/255.f);
	GLfloat diffuseMaterial1[] = {r, g, b, 1.0f};
	table->setMaterial(ambientMaterial1, diffuseMaterial1);
	scenario->objects.push_back(table);

	EDMesh* ball = new EDMesh("ball", path, filename3);
	r = (193/255.f);
	g = (25/255.f);
	b = (22/255.f);
	GLfloat ambientMaterial2[] = {r, g, b, 1.0f};
	r = (239/255.f);
	g = (68/255.f);
	b = (58/255.f);
	GLfloat diffuseMaterial2[] = {r, g, b, 1.0f};
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
	r = (77/255.f);
	g = (78/255.f);
	b = (62/255.f);
	GLfloat ambientMaterial3[] = {r, g, b, 1.0f};
	r = (207/255.f);
	g = (226/255.f);
	b = (198/255.f);
	GLfloat diffuseMaterial3[] = {r, g, b, 1.0f};
	luxor->setMaterial(ambientMaterial3, diffuseMaterial3);
	luxor->scale(EDPoint(1.f,1.f,1.f), 0.9f);
	luxor->rotate(EDPoint(0.f,1.f,0.f), 60);
	luxor->translate(EDPoint(-.6f,3.25f,2.5f));
	luxor->updateMinValue();
	scenario->objects.push_back(luxor);
}

StandLuxorScene::~StandLuxorScene(void)
{ }