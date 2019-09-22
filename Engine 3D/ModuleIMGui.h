#pragma once
#include "Module.h"
#include "imgui.h"


enum ObjectType
{
	Type_Sphere = 0,
	Type_Cylinder,
	Type_Capsule,
	Type_AABB,
	Type_OBB,
	Type_Frustum,
	Type_Plane,
	Type_Segment,
	Type_Ray,
	Type_Convex_Hull,
	Type_Mesh,
	Type_Triangle
};


class ModuleIMGui :
	public Module
{
public:
	ModuleIMGui(Application * app, bool start_enabled = true);
	~ModuleIMGui();

	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void Draw();


public:

	bool showDemo = false;
	bool showMath = false;

	float posx1 = 0.0f;
	float posx2 = 5.0f;

	int current_object1 = Type_Sphere;
	int current_object2 = Type_Sphere;
};

