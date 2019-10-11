#pragma once
#include "Module.h"
#include "Primitive.h"
#include "Globals.h"
#include <vector>

struct Mesh
{
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;
};

class ModuleImport : public Module
{
public:
	ModuleImport(Application* app, bool start_enabled = true);
	~ModuleImport();

	bool Start();
	update_status Update(float dt);

	void Import(const char* path);

	bool CleanUp();

public:
	Mesh m;
};

