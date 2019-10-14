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

	bool Start();
	void Draw();
	void AddLog(const char* fmt, ...) IM_FMTARGS(2);
	void ClearLog();
	static char* Strdup(const char* str) { size_t len = strlen(str) + 1; void* buff = malloc(len); return (char*)memcpy(buff, (const void*)str, len); }
	static int   Stricmp(const char* str1, const char* str2) { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
	static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }



private:

	char                  InputBuf[256];
	ImVector<char*>       Items;
	bool                  ScrollToBottom;
	ImVector<char*>       History;
	int                   HistoryPos;
	ImVector<const char*> Commands;

	bool on = false;
};


