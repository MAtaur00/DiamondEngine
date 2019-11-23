#include "ModuleIMGui.h"
#include "Globals.h"
#include "imgui.h"
#include "ModuleWindow.h"
#include "SDL/include/SDL.h"
#include <vector>


class ImGuiConsole
{
public:
	ImGuiConsole();
	~ImGuiConsole();

	void Draw();

	//void AddLog(const char*, ...) IM_FMTARGS(2);
	//void ClearLog();

	void LogConsole(const char * consoleText);	

public:
	ImGuiTextBuffer textBuff;
	bool canScroll = false;
};