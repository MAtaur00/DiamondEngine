#include "ModuleTime.h"



Time::Time(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}


Time::~Time()
{
}

bool Time::Start()
{
	timer.Start();

	return true;
}