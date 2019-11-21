#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Glew/include/glew.h"

#pragma comment(lib, "Glew/libx86/glew32.lib")

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update()
{
	PrimitivePlane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	return UPDATE_CONTINUE;
}