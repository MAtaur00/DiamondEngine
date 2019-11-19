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

	void SaveScene(const char* name);

	void LoadScene(const char* name);

	void SaveGameObjects(JSON_Array* &parent, GameObject* current);

	GameObject* GetGO(unsigned int uuid);

public:
	GameObject* root = nullptr;

	std::list<GameObject*> gameObjects;
};