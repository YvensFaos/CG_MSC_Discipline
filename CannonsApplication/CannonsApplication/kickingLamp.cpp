#include "kickingLamp.h"

#include "edmesh.h"

#define A   2.0f
#define W   6.0f
#define O   0.0f*pi180
#define E   2.718282f
#define K   0.5f

void kickingLamp(float elapsedTime, GObject* object)
{
	EDMesh* luxor = (EDMesh*)object;

	float x = luxor->min.x / 2.0f;
	float y = A * abs((float) sin(W*x + O)) * pow(E, -K*x);
	printf("y = %f\n",y);
	if(y > 50)
	{
		printf("EPA!\n");
	}
	luxor->translate(EDPoint(0.0f, -luxor->min.y, 0.0f));
	luxor->params[0] += elapsedTime;

	if(luxor->min.x > 20.0f)
	{
		elapsedTime = 0;
	}
	luxor->translate(EDPoint(elapsedTime/4.0f, y, 0.0f));
}

KickingLamp::KickingLamp(void) : Scene()
{
	scenario = new Scenario();
	camera = new EDCamera(new EDPoint(0.f, 8.3f, 22.4f), new EDPoint(1.7f, 7.7f, 17.7f), 0.05f, 300.0f, 45.0f);

	/*
	0   8.3 22.4
1.7 7.7 17.7
	*/
	char* path = "C:/Users/Yvens/Documents/Visual Studio 2012/Projects/DisciplinaCG/CannonsApplication/Objs/";
	//char* path = "C:/Users/Yvens/Documents/GitHub/DisciplinaCG/CannonsApplication/Objs/";
	char* filename2 = "luxor_203.txt";

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
