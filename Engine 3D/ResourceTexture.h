#pragma once
#include "Resource.h"
class ResourceTexture :
	public Resource
{
public:
	ResourceTexture(const char * path);
	~ResourceTexture();
};