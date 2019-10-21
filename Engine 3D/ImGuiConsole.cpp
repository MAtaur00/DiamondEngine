#include "ImGuiConsole.h"
#include "Application.h"
#include "Glew/include/glew.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Psapi.h"
#include "Windows.h"
#include "ModuleWindow.h"

ImGuiConsole::ImGuiConsole()
{	
}

ImGuiConsole::~ImGuiConsole()
{
}

void ImGuiConsole::LogConsole(const char * consoleText)
{
	textBuff.appendf(consoleText);
	canScroll = true;
}


void ImGuiConsole::Draw()
{
	ImGui::Begin("Console", &App->imgui->showConsole, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove);

	if (ImGui::Button("Clear", ImVec2(400, 20)))
		textBuff.clear();

	ImGui::Separator();

	ImGui::TextWrapped(textBuff.begin());
	if (canScroll)
		ImGui::SetScrollY(1.0f);

	canScroll = false;

	ImGui::End();
}
