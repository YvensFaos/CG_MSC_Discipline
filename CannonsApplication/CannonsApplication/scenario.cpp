#include "scenario.h"

Scenario::Scenario(void)
{ }

Scenario::~Scenario(void)
{ }

void Scenario::update(float elapsedTime)
{
	std::list<GObject*>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++)
	{
		(*i)->update(elapsedTime);
		(*i)->callUpdate(elapsedTime, *i);
	}
}

void Scenario::draw(void)
{
	std::list<GObject*>::iterator i;
	for (i = objects.begin(); i != objects.end(); i++)
	{
		(*i)->draw();
	}
}