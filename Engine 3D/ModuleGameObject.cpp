#include "ModuleGameObject.h"



ModuleGameObject::ModuleGameObject(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleGameObject::~ModuleGameObject()
{
}

bool ModuleGameObject::Init()
{
	root = new GameObject(nullptr, "Root");
	return true;
}
