#ifndef __SCENE__
#define __SCENE__

#include "edcamera.h"
#include "scenario.h"

class Scene
{
public:
	EDCamera* camera;
	Scenario* scenario;

	Scene(void)
	{ }

	~Scene(void)
	{
		if(camera)
			delete camera;
		if(scenario)
			delete scenario;
	}
};

#endif