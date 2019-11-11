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
	CreateDirectory("Library", NULL);
	CreateDirectory("Library/Models", NULL);
	CreateDirectory("Library/Textures", NULL);

	return true;
}

void ModuleResources::SaveFile(uint size, char* output_file, ResourceType type, uint uuid, const char* path)
{
	string direction = GetDirection(type, uuid, path);

	ofstream file(direction.c_str(), ios::out | ios::binary);

	if (file.is_open())
	{
		file.write(output_file, size);
		file.close();
	}
}

string ModuleResources::GetDirection(ResourceType type, uint uuid, const char* path)
{
	string filePath = "Library/";

	switch (type)
	{
	case ResourceType::Mesh:
	{
		filePath += "Models/";
		filePath += to_string(uuid);
		filePath += ".dmnd";
	}
		break;
	case ResourceType::Texture:
	{
		filePath += "Textures/";
		uint initialPos = filePath.find_last_of("\\") + 1;
		uint finalPos = filePath.find_last_of(".") + 1;
		filePath.substr(initialPos, (finalPos - initialPos)) + "dds";
	}
		break;
	default:
		break;
	}

	return filePath;
}

Resource* ModuleResources::GetResource(ResourceType type, const char * path)
{
	for (std::list<Resource*>::iterator it = resources.begin(); it != resources.end(); ++it)
	{
		if ((*it)->type == type)
		{
			if (strcmp((*it)->name.data(), path) == 0)
				return *it;
		}
	}
	return nullptr;
}