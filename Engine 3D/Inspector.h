#pragma once
#include "ModuleIMGui.h"
#include "imgui.h"

class GameObject;

class Inspector
{
public:
	Inspector();
	~Inspector();

	void Draw();
	void NewObjectsToDelete(GameObject* object);
};

