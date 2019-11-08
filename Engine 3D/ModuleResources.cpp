#include "ModuleResources.h"



ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Import(const char * file, const char * path, std::string & output_file)
{
	return false;
}

bool ModuleResources::Import(const void * buffer, uint size, std::string & output_file)
{
	return false;
}

bool ModuleResources::Load(const char * exported_file, ComponentTexture * resource)
{
	return false;
}

bool ModuleResources::LoadCheckers(ComponentTexture * resource)
{
	return false;
}