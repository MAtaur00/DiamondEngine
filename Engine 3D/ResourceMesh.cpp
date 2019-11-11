#include "ResourceMesh.h"


ResourceMesh::ResourceMesh(const char * path) : Resource(ResourceType::Mesh, path)
{
}


ResourceMesh::~ResourceMesh()
{
}

void ResourceMesh::Unload()
{
	/// TODO
}