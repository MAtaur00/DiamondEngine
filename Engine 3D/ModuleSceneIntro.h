#pragma once
#include "Module.h"
#include "Globals.h"
#include "GameObject.h"
#include "QuadTree.h"
#include "ImGuizmo/ImGuizmo.h"

struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	GameObject* current_object = nullptr;

	Quad_Tree quadtree;

	ImGuizmo::OPERATION guiz_operation = ImGuizmo::BOUNDS;

	ImGuizmo::MODE guiz_mode = ImGuizmo::WORLD;
};