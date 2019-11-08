#pragma once
#include "Module.h"
#include <string>
#include "ComponentTexture.h"

enum ResourceType
{
	Mesh = 0,
	Texture
};

class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	bool Init();

	void SaveFile(uint size, char* output_file, ResourceType type, uint uuid, const char* path = nullptr);

	std::string GetDirection(ResourceType type, uint uuid, const char* path = nullptr);
};