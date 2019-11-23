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

	ImGui::SetWindowPos(ImVec2(0.0f, (App->window->height) / 6.0f * 4.75f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(App->window->width , (App->window->height) / 6.0f * 1.25f), ImGuiCond_Always);

	if (ImGui::Button("Clear", ImVec2(400, 20)))
		textBuff.clear();

	ImGui::Separator();

	ImGui::BeginChildFrame(1, ImVec2(App->window->width - 50, (App->window->height / 8.0f)), ImGuiCond_Always);

	ImGui::TextWrapped(textBuff.begin());

	if (canScroll)
		ImGui::SetScrollHere(1.0f);

	ImGui::EndChildFrame();		

	canScroll = false;

	ImGui::End();
}
