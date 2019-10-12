#pragma once
#include "Component.h"
class ComponentLight :
	public Component
{
public:
	ComponentLight(GameObject* parent);
	~ComponentLight();
};

