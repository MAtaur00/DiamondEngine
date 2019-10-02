#include "ModuleIMGui.h"
#include "Globals.h"
#include "imgui.h"

class ImGuiConfig
{
public:
	ImGuiConfig();
	~ImGuiConfig();

	bool Start();

	void Draw();
};