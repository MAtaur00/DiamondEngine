#pragma once
#include "Component.h"
#include "ComponentTransform.h"

#include <string>
#include <vector>
#include <list>

class GameObject
{
public:
	GameObject(GameObject* parent, const char* name = nullptr);
	~GameObject();

public:
	bool active = true;
	std::string name = "gameObject";
	std::vector<Component*> components;
	ComponentTransform* transform = nullptr;
	GameObject* parent = nullptr;
	std::list<GameObject*> childs;
};