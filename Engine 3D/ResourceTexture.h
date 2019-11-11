#pragma once
#include "Resource.h"
class ResourceTexture :
	public Resource
{
public:
	ResourceTexture(const char * path);
	~ResourceTexture();

	void Unload();

public:
	uint id = 0u;
};