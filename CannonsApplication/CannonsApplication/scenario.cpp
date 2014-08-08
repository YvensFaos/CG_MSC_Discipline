#include "scenario.h"

Scenario::Scenario(void)
{ }

Scenario::~Scenario(void)
{ }

void Scenario::update(float elapsedTime)
{
	for (std::list<GObject>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		it->update(elapsedTime);
	}
}

void Scenario::draw(void)
{
	for (std::list<GObject>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		it->draw();
	}
}