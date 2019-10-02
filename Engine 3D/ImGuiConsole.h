#include "ModuleIMGui.h"
#include "Globals.h"
#include "imgui.h"

class ImGuiConsole
{
public:
	ImGuiConsole();
	~ImGuiConsole();

	bool Start();

	void Draw();
};