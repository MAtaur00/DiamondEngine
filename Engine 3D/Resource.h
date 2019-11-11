#pragma once
#include "Globals.h"
#include <string>

enum class ResourceType
{
	None = 0,
	Mesh,
	Texture
};

class Resource
{
public:
	Resource(ResourceType type, const char* path) : type(type), name(path) {};
	~Resource();

	virtual void Unload() {};

	bool operator==(Resource other);

public:

	std::string name;
	ResourceType type = ResourceType::None;
	uint usage = 0u;
};

