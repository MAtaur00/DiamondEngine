#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "ModuleImport.h"
#include <vector>
#include "ComponentMesh.h"
#include "ComponentCamera.h"

#define MAX_LIGHTS 8

class Mesh;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	void OnResize(int width, int height);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	std::vector<ComponentMesh*> mesh_list;

	bool vsync = true;

	bool drawBoxes = false;

	bool paintTextures = true;

	ComponentCamera* current_cam = nullptr;

	ComponentCamera* play_cam = nullptr;
};