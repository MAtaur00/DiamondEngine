#include "ImGuiConsole.h"
#include "Application.h"
#include "Glew/include/glew.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Psapi.h"
#include "Windows.h"


ImGuiConsole::ImGuiConsole()
{

}

ImGuiConsole::~ImGuiConsole()
{

}

bool ImGuiConsole::Start()
{
	bool ret = true;

	return ret;
}

void ImGuiConsole::Draw()
{
	if (ImGui::Begin("Console", &App->imgui->showConsole))
	{

	}
	ImGui::End();
}