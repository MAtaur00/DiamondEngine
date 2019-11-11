#pragma once
#include "Resource.h"
class ResourceTexture :
	public Resource
{
public:
	ResourceTexture(const char * path);
	~ResourceTexture();

public:
	uint id = 0u;
};