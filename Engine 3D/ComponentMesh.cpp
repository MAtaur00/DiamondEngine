#include "ComponentMesh.h"
#include "GameObject.h"



ComponentMesh::ComponentMesh(GameObject* parent) : Component(parent, CompMesh)
{
	parent->components.push_back(this);
}


ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::Inspector()
{
}
