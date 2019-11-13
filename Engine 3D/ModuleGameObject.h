#pragma once
#include "Module.h"
#include "GameObject.h"
#include <list>
class ModuleGameObject :
	public Module
{
public:
	ModuleGameObject(Application * app, bool start_enabled = true);
	~ModuleGameObject();

	bool Init();

public:
	GameObject* root = nullptr;

	std::list<GameObject*> gameObjects;
};