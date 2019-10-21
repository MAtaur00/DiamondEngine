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