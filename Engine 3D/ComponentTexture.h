#pragma once
#include "Component.h"
#include "GameObject.h"

class ComponentTexture :
	public Component
{
public:
	ComponentTexture(GameObject* parent);
	~ComponentTexture();

	void Inspector();
};

