#pragma once
#include "Module.h"
class ModulePicking :
	public Module
{
public:
	ModulePicking(Application* app, bool start_enabled = true);
	~ModulePicking();

	update_status Update(float dt);
};

