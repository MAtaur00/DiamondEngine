#include "ModuleImportFBX.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"

#include <gl/GL.h>

ModuleImportFBX::ModuleImportFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleImportFBX::~ModuleImportFBX()
{
}


bool ModuleImportFBX::Start() {

	return ret;
}

void ModuleImportFBX::Draw() {


}

update_status ModuleImportFBX::Update(float dt) {


	return UPDATE_CONTINUE;
}