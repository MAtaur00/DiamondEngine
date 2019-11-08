#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleIMGui.h"
#include "ModuleSceneIntro.h"
#include "ModuleGeometry.h"
#include "ModuleImport.h"
#include "ModuleGameObject.h"
#include "ModuleResources.h"

#include <list>
#include <vector>


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleIMGui* imgui;
	ModuleSceneIntro* sceneIntro;
	ModuleGeometry* geometry;
	ModuleImport* import;
	ModuleGameObject* game_object;
	ModuleResources* resources;

	int width = 0;
	int height = 0;

private:

	Timer	ms_timer;
	float	dt;
	std::list<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	bool toCap = false;

	int capFrames = 60;

	std::vector<float> fps_log;
	std::vector<float> ms_log;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};
extern Application* App;