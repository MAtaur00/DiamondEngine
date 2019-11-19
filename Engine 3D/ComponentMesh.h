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

	void Save(JSON_Object* parent);

	void Load(JSON_Object* parent);

public:
	ResourceMesh* mesh;

	bool print = true;

	bool printVertexNormals = false;
	bool printFacesNormals = false;
};