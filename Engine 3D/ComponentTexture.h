#pragma once
#include "Component.h"
#include "GameObject.h"
#include <string>

class ComponentTexture :
	public Component
{
public:
	ComponentTexture(GameObject* parent);
	~ComponentTexture();

	void Inspector();

	unsigned int GetID();

public:
	unsigned int tex_id = 0u;

	std::string name;

	std::string path;

	bool print = true;

	bool checkers = false;
};

