#pragma once
#include "Module.h"
#include "Primitive.h"
#include "Globals.h"

class ModuleImportFBX : public Module
{
public:
	ModuleImportFBX(Application* app, bool start_enabled = true);
	~ModuleImportFBX();

	bool Start();
	update_status Update(float dt);

	Mesh* Import(const char* path);

	bool CleanUp();
};

