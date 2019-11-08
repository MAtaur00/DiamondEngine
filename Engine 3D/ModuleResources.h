#pragma once
#include "Module.h"
#include <string>
#include "ComponentTexture.h"


class ModuleResources : public Module
{
public:
	ModuleResources(Application* app, bool start_enabled);
	~ModuleResources();

	bool Import(const char* file, const char* path, std::string& output_file);
	bool Import(const void* buffer, uint size, std::string& output_file);
	bool Load(const char* exported_file, ComponentTexture* resource);
	bool LoadCheckers(ComponentTexture* resource);
};

