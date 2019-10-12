#pragma once
#include "Module.h"
class ModuleGameObject :
	public Module
{
public:
	ModuleGameObject(Application * app, bool start_enabled);
	~ModuleGameObject();
};

