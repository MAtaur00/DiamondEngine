#pragma once
#include "imgui.h"
#include "ModuleIMGui.h"

class GameObject;

class Hierarchy
{
public:
	Hierarchy();
	~Hierarchy();

	bool Start();

	void Draw();

	void DrawGameObjects(GameObject* current);
};