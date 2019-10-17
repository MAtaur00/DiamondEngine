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

	void AddLog(const char*, ...) IM_FMTARGS(2);
	void ClearLog();


private:
	char inputBuf[256];
	ImVector<char*> items;
	bool scrollToBottom;
	static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
	static char* Strdup(const char* str) { size_t len = strlen(str) + 1; void* buff = malloc(len); return (char*)memcpy(buff, (const void*)str, len); }
	

	bool on = false;
};


