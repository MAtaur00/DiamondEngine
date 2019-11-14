#pragma once
#include "pcg/pcg_basic.h"
class GameObject;

enum Object_Type
{
	None = -1,

	CompTransform = 0,
	CompMesh,
	CompTexture,
	CompCamera,
	CompLight
};

class Component
{
public:
	Component(GameObject* parent, Object_Type type) : gameObject(parent), type(type) { uuid = pcg32_random(); }
	~Component() {}

	virtual void Inspector() {}
public:
	GameObject* gameObject = nullptr;
	Object_Type type;

	unsigned int uuid = 0u;
};