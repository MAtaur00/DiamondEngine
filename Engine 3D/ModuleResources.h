#pragma once
#include "Module.h"
#include <string>
#include "ComponentTexture.h"
#include "Resource.h"
#include <list>

class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled = true);
	~ModuleResources();

	bool Init();

	void SaveFile(uint size, char* output_file, ResourceType type, uint uuid, const char* path = nullptr);

	std::string GetDirection(ResourceType type, uint uuid, const char* path = nullptr);

	Resource* GetResource(ResourceType type, const char* path);

public:
	
	std::list<Resource*> resources;
};