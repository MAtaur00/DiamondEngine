#include "ModuleResources.h"
#include <fstream>
#include <iostream>
using namespace std;


ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Init()
{
	CreateDirectory("Llibrary", NULL);
	CreateDirectory("Llibrary/Meshes", NULL);
	CreateDirectory("Llibrary/Textures", NULL);

	return true;
}

void ModuleResources::SaveFile(uint size, char * output_file, ResourceType type, uint uuid, const char * path)
{
	
}

string ModuleResources::GetDirection(ResourceType type, uint uuid, const char * path)
{
	string filePath = "Library/";

	switch (type)
	{
	case Mesh:
		filePath += "Models/";
		filePath += to_string(uuid);
		filePath += ".dmnd";
		break;
	case Texture:
		filePath += "Textures/";
		uint initialPos = filePath.find_last_of("\\") + 1;
		uint finalPos = filePath.find_last_of(".") + 1;
		filePath.substr(initialPos, (finalPos - initialPos)) + "dds";
		break;
	default:
		break;
	}

	return filePath;
}