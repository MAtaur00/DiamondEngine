#include "ModuleGeometry.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"

#include <gl/GL.h>

ModuleGeometry::ModuleGeometry(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleGeometry::~ModuleGeometry()
{
}


bool ModuleGeometry::Start() {

	return ret;
}

void ModuleGeometry::Draw(){
	
}

update_status ModuleGeometry::Update() 
{
	return UPDATE_CONTINUE;
}