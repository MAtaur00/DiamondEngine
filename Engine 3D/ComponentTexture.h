#pragma once
#include "Component.h"
#include "GameObject.h"
#include "ResourceTexture.h"
#include <string>

class ComponentTexture :
	public Component
{
public:
	ComponentTexture(GameObject* parent);
	~ComponentTexture();

	void Inspector();

	unsigned int GetID();

	void Save(JSON_Object* parent);

	void Load(JSON_Object* parent);

public:
	ResourceTexture* RTexture;

	std::string name;

	std::string path;

	bool print = true;

	bool checkers = false;
};

