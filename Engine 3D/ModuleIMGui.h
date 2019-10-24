#pragma once
#include "Module.h"
#include "imgui.h"
#include <vector>


enum ObjectType
{
	Type_Sphere = 0,
	Type_Capsule,
	Type_AABB,
	Type_OBB,
	Type_Ray,
	Type_Triangle
};

class ImGuiConfig;
class ImGuiAbout;
class ImGuiConsole;
class Hierarchy;
class Inspector;
class Shapes;

class ModuleIMGui : public Module
{
public:
	ModuleIMGui(Application * app, bool start_enabled = true);
	~ModuleIMGui();

	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void Draw();


public:

	ImGuiConfig* gui_config;
	ImGuiAbout* gui_about;
	ImGuiConsole* gui_console;
	Hierarchy* hierarchy;
	Inspector* inspector;
	Shapes* shapes;

	bool showDemo = false;
	bool showMath = false;
	bool showRNG = false;
	bool showAbout = false;
	bool showHierarchy = true;
	bool showInspector = true;
	bool showConfiguration = false;
	bool showConsole = true;
	bool showShapes = false;

	float posx1 = 0.0f;
	float posx2 = 5.0f;

	int fps1 = 0;

	int current_object1 = Type_Sphere;
	int current_object2 = Type_Sphere;

	float randomFloat = 0.0f;

	int randomInt = 0;

	int buttonMinMax[2] = { 0, 10 };

	std::vector<float> ram_log;

	float brightnessPos = 1.0f;

	int widthPos = 1280;
	int heightPos = 950;

	bool fullscreen = false;
	bool borderless = false;
	bool resizable = false;
	bool fullDesktop = false;
};

