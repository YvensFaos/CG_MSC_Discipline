#ifndef __SCENARIO_H__
#define __SCENARIO_H__

#include <iostream>
#include <list>
#include "geometricObjects.h"

class Scenario
{
public:
	std::list<GObject*> objects;

	Scenario(void);
	~Scenario(void);

	void update(float elapsedTime);
	void draw(void);
};

#endif