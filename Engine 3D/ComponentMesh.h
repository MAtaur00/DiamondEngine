#pragma once
#include "Component.h"
#include "ResourceMesh.h"
#include <string>

class ComponentMesh :
	public Component
{
public:
	ComponentMesh(GameObject* parent);
	~ComponentMesh();

	void Inspector();

	void Draw();



public:
	ResourceMesh* mesh;
	std::string name;

	bool print = true;

	bool printVertexNormals = false;
	bool printFacesNormals = false;
};