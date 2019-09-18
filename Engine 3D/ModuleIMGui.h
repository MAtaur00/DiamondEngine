#pragma once
#include "Module.h"
#include "imgui.h"

class ModuleIMGui :
	public Module
{
public:
	ModuleIMGui(Application * app, bool start_enabled = true);
	~ModuleIMGui();

	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void Draw();


public:

	bool showDemo = false;
};

