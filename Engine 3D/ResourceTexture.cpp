#include "ResourceTexture.h"



ResourceTexture::ResourceTexture(const char * path) : Resource(ResourceType::Texture, path)
{
}


ResourceTexture::~ResourceTexture()
{
}

void ResourceTexture::Unload()
{
	/// TODO
}
