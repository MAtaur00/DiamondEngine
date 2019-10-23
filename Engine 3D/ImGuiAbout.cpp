#include "ImGuiAbout.h"
#include "Application.h"
#include "Glew/include/glew.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Psapi.h"
#include "Windows.h"


ImGuiAbout::ImGuiAbout()
{

}

ImGuiAbout::~ImGuiAbout()
{

}

void ImGuiAbout::Draw()
{
	if (ImGui::Begin("About", &App->imgui->showAbout))
	{
		if (ImGui::Button("Repository", ImVec2(150, 25)))
			ShellExecuteA(NULL, "Open", "https://github.com/MAtaur00/DiamondEngine", NULL, NULL, SW_SHOWNORMAL);

		ImGui::Text("Made by:");
		if (ImGui::Button("Marc Tarres", ImVec2(150, 25)))
			ShellExecuteA(NULL, "Open", "https://github.com/MAtaur00", NULL, NULL, SW_SHOWNORMAL);
		ImGui::SameLine();
		if (ImGui::Button("Aleix Castillo", ImVec2(150, 25)))
			ShellExecuteA(NULL, "Open", "https://github.com/AleixCas95", NULL, NULL, SW_SHOWNORMAL);

		ImGui::Separator();
		ImGui::Text("Libraries used in this engine");

		std::string nameStr = "ImGui ";
		nameStr += ImGui::GetVersion();
		if (ImGui::Button(nameStr.data(), ImVec2(125, 20)))
			ShellExecuteA(NULL, "Open", "https://github.com/ocornut/imgui/releases", NULL, NULL, SW_SHOWNORMAL);

		SDL_version current;
		SDL_VERSION(&current);
		char nameChar[25];
		sprintf_s(nameChar, 25, "SDL %d.%d.%d", current.major, current.minor, current.patch);
		if (ImGui::Button(nameChar, ImVec2(125, 20)))
			ShellExecuteA(NULL, "Open", "https://www.libsdl.org/download-2.0.php", NULL, NULL, SW_SHOWNORMAL);

		int major, minor;
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
		sprintf_s(nameChar, 25, "OpenGL %i.%i", major, minor);
		if (ImGui::Button(nameChar, ImVec2(125, 20)))
			ShellExecuteA(NULL, "Open", "https://www.opengl.org", NULL, NULL, SW_SHOWNORMAL);

		sprintf_s(nameChar, 25, "MathGeoLib 1.5");
		if (ImGui::Button(nameChar, ImVec2(125, 20)))
			ShellExecuteA(NULL, "Open", "https://github.com/juj/MathGeoLib/releases/tag/v1.5", NULL, NULL, SW_SHOWNORMAL);

		sprintf_s(nameChar, 25, "PCG 0.94");
		if (ImGui::Button(nameChar, ImVec2(125, 20)))
			ShellExecuteA(NULL, "Open", "http://www.pcg-random.org/download.html", NULL, NULL, SW_SHOWNORMAL);

		sprintf_s(nameChar, 25, "Assimp 3.3");
		if (ImGui::Button(nameChar, ImVec2(125, 20)))
			ShellExecuteA(NULL, "Open", "http://www.assimp.org", NULL, NULL, SW_SHOWNORMAL);

		sprintf_s(nameChar, 25, "DevIL 1.8");
		if (ImGui::Button(nameChar, ImVec2(125, 20)))
			ShellExecuteA(NULL, "Open", "http://openil.sourceforge.net", NULL, NULL, SW_SHOWNORMAL);

		ImGui::Separator();
		ImGui::TextWrapped("MIT License Copyright (c) 2019 Marc Tarres and Aleix Castillo");

		ImGui::NewLine();

		ImGui::TextWrapped("Permission is hereby granted, free of charge, to any person obtaining a copy of this software"
			"and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,"
			"merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:");

		ImGui::NewLine();

		ImGui::TextWrapped("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");

		ImGui::NewLine();

		ImGui::TextWrapped("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A"
			"PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,"
			"WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");
	}
	ImGui::End();
}