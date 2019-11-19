#pragma once
#include "Component.h"
#include "ComponentTransform.h"

#include <string>
#include <list>

class GameObject
{
public:
	GameObject(GameObject* parent, const char* name = nullptr, bool addToList = true);
	~GameObject();

	void RealDelete();

	bool HasComponent(Object_Type type);

	Component* GetComponent(Object_Type type);

	void Save(JSON_Object* parent);

	void Load(JSON_Object* info);

	bool SetParent(GameObject* parent);

public:
	std::string name = "gameObject";
	std::list<Component*> components;
	ComponentTransform* transform = nullptr;
	GameObject* parent = nullptr;
	std::list<GameObject*> childs;

	AABB originalBoundingBox;
	AABB boundingBox;

	bool active = true;
	bool isStatic = false;

	unsigned int uuid = 0u;

	unsigned int parentUUID = 0u;
};