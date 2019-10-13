#pragma once
#include "Component.h"
#include "Primitive.h"
#include <string>

class ComponentMesh :
	public Component
{
public:
	ComponentMesh(GameObject* parent);
	~ComponentMesh();

public:
	Mesh* mesh;
	std::string name;
};