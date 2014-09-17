#include "kickingLamp.h"

#include "edmesh.h"

#define A   1.0f
#define W   1.0f
#define O   0.0f
#define E   2.718282f
#define K  -0.35f

void kickingLamp(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;

	float y = luxor->params[1] * pow(abs((float) sin(W*luxor->params[0] + O)), K*luxor->params[0]);
	printf("y = %f\n",y);
	luxor->translate(EDPoint(0.0f, -luxor->min.y, 0.0f));
	luxor->translate(EDPoint(0.0f, y, 0.0f));

	luxor->params[0] += elapsedTime;
}

KickingLamp::KickingLamp(void) : Scene()
{
	scenario = new Scenario();
	camera = new EDCamera(new EDPoint(-0.7f, 2.0f, 6.59f), new EDPoint(1.01f, 1.4f, 1.9f), 0.05f, 300.0f, 45.0f);

	//char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename1 = "table3.txt";
	char* filename2 = "luxor_203.txt";
	char* filename3 = "ball.txt";

	float r = 0; 
	float g = 0; 
	float b = 0;
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
	luxor->setCallUpdate(kickingLamp);

	luxor->params = new float[2];
	luxor->params[0] = 0.0f;
	luxor->params[1] = luxor->min.y;

	scenario->objects.push_back(luxor);
}

KickingLamp::~KickingLamp(void)
{ }
