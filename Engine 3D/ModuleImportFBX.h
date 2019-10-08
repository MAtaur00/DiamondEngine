#pragma once
#include "Module.h"
#include "Primitive.h"
#include "Globals.h"

struct dataFBX
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;
	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

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

