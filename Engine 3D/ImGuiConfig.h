#include "ModuleIMGui.h"
#include "Globals.h"
#include "imgui.h"
#include "Glew/include/glew.h"

class ImGuiConfig
{
public:
	ImGuiConfig();
	~ImGuiConfig();

	bool Start();

	void SetState(GLenum capability, bool enable) const;

	void Draw();
};