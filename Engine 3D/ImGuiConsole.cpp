#include "ImGuiConsole.h"
#include "Application.h"
#include "Glew/include/glew.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Psapi.h"
#include "Windows.h"
#include "ModuleWindow.h"

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

ImGuiConsole::ImGuiConsole()
{
	ClearLog();
	memset(inputBuf, 0, sizeof(inputBuf));
	AddLog("Welcome to ImGui!");
	
}

ImGuiConsole::~ImGuiConsole()
{
	ClearLog();
}



void ImGuiConsole::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	/*items.push_back(Strdup(fmt));
	scrollToBottom = true;*/
}


void ImGuiConsole::ClearLog()
{
	/*if (items.Size > 0) {
		for (int i = 0; i < items.Size; i++) {
			free(items[i]);
		}
	}
	items.clear();
	scrollToBottom = true;*/
}



void ImGuiConsole::Draw()
{
	ImGui::Begin("Console", &on, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove);

	//ImGui::SetWindowPos({ 0.0f, (float)App->height - ((225 * App->height) / 1024) });
	//ImGui::SetWindowSize(ImVec2(App->width, (225 * App->height) / 1024), ImGuiCond_Always);

	//if (ImGui::SmallButton("Clear")) {
	//	ClearLog();
	//}
	//ImGui::SameLine();
	//if (ImGui::SmallButton("Scrool to bottom")) {
	//	scrollToBottom = true;
	//}
	//ImGui::Separator();

	//ImGui::BeginChild(("Scroll"), ImVec2{ 0,-ImGui::GetItemsLineHeightWithSpacing() }, false, ImGuiWindowFlags_HorizontalScrollbar);
	//if (ImGui::BeginPopupContextWindow()) {
	//	if (ImGui::Selectable("Clear")) {
	//		ClearLog();
	//	}
	//	ImGui::EndPopup();
	//}

	////Write logs
	//for (int i = 0; i < items.Size; i++) {
	//	const char* currentItem = items[i];
	//	ImVec4 colour = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	//	if (strstr(currentItem, "[error]")) {
	//		colour = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
	//	}
	//	else if (strncmp(currentItem, "# ", 2) == 0) {
	//		colour = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
	//	}
	//	ImGui::PushStyleColor(ImGuiCol_Text, colour);
	//	ImGui::TextUnformatted(currentItem);
	//	ImGui::PopStyleColor();
	//}
	//if (scrollToBottom == true) {
	//	ImGui::SetScrollHere();
	//}
	//scrollToBottom = false;
	ImGui::End();

}
