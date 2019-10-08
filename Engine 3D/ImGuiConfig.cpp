#include "ImGuiConfig.h"
#include "Application.h"
#include "Glew/include/glew.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Psapi.h"
#include "Windows.h"


ImGuiConfig::ImGuiConfig()
{

}

ImGuiConfig::~ImGuiConfig()
{

}

bool ImGuiConfig::Start()
{
	bool ret = true;

	return ret;
}

void ImGuiConfig::Draw()
{
	if (ImGui::Begin("Configuration", &App->imgui->showConfiguration))
	{
		if (ImGui::CollapsingHeader("Application"))
		{
			char buf[64] = "Diamond Engine";
			if (ImGui::InputText("App Name", buf, IM_ARRAYSIZE(buf)))
			{
				App->window->SetTitle(buf);
			}
			char buf2[64] = "UPC CITM";
			if (ImGui::InputText("Organization", buf2, IM_ARRAYSIZE(buf2)))
			{

			}
			ImGui::SliderInt("Max FPS", &App->capFrames, 0, 125);

			ImGui::Text("Limit Framerate: %i", App->capFrames);
			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", App->fps_log[App->fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &App->fps_log[0], App->fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));

			sprintf_s(title, 25, "Milliseconds %.1f", App->ms_log[App->ms_log.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &App->ms_log[0], App->ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

			sprintf_s(title, 25, "Memory Consumption %.1f", App->imgui->ram_log[App->imgui->ram_log.size() - 1]);
			ImGui::PlotHistogram("##memory consumption", &App->imgui->ram_log[0], App->imgui->ram_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));



			ImGui::Text("Total Reported Mem: %i", 0);
			ImGui::Text("Total Actual Mem: %i", 0);
			ImGui::Text("Peak Reported Mem: %i", 0);
			ImGui::Text("Peak Actual Mem: %i", 0);
			ImGui::Text("Accumulated Reported Mem: %i", 0);
			ImGui::Text("Accumulated Actual Mem: %i", 0);
			ImGui::Text("Accumulated Alloc Unit Count: %i", 0);
			ImGui::Text("Total Alloc Unit Count: %i", 0);
		}
		if (ImGui::CollapsingHeader("Window"))
		{
			if (ImGui::SliderFloat("Brightness", &App->imgui->brightnessPos, 0.0f, 1.0f))
			{
				SDL_SetWindowBrightness(App->window->window, App->imgui->brightnessPos);
			}
			if (ImGui::SliderInt("Width", &App->imgui->widthPos, 640, 1920))
			{
				SDL_SetWindowSize(App->window->window, App->imgui->widthPos, App->imgui->heightPos);
				App->renderer3D->OnResize(App->imgui->widthPos, App->imgui->heightPos);
			}
			if (ImGui::SliderInt("Height", &App->imgui->heightPos, 480, 1080))
			{
				SDL_SetWindowSize(App->window->window, App->imgui->widthPos, App->imgui->heightPos);
				App->renderer3D->OnResize(App->imgui->widthPos, App->imgui->heightPos);
			}

			if (ImGui::Checkbox("Fullscreen", &App->imgui->fullscreen))
			{
				App->window->SetFullscreen(App->imgui->fullscreen);
			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Resizable", &App->imgui->resizable))
			{
				App->window->SetResizable(App->imgui->resizable);
			}

			if (ImGui::Checkbox("Borderless", &App->imgui->borderless))
			{
				App->window->SetBorderless(App->imgui->borderless);
			}

			ImGui::SameLine();

			if (ImGui::Checkbox("Full Desktop", &App->imgui->fullDesktop))
			{
				App->window->SetFullDesktop(App->imgui->fullDesktop);
			}

			

			if (ImGui::IsItemHovered)
			{
				ImGui::SetTooltip("Restart to apply");
			}

			GLenum capability = 0;

			capability = GL_DEPTH_TEST;
			bool depthTest = glIsEnabled(capability);
			if (ImGui::Checkbox("GL_DEPTH_TEST", &depthTest))
				SetState(capability, depthTest);


			capability = GL_CULL_FACE;
			bool cullFace = glIsEnabled(capability);
			if (ImGui::Checkbox("GL_CULL_FACE", &cullFace))
				SetState(capability, cullFace);

			capability = GL_LIGHTING;
			bool lighting = glIsEnabled(capability);
			if (ImGui::Checkbox("GL_LIGHTING", &lighting))
				SetState(capability, lighting);

			capability = GL_COLOR_MATERIAL;
			bool colorMaterial = glIsEnabled(capability);
			if (ImGui::Checkbox("GL_COLOR_MATERIAL", &colorMaterial))
				SetState(capability, colorMaterial);

			capability = GL_TEXTURE_2D;
			bool texture2D = glIsEnabled(capability);
			if (ImGui::Checkbox("GL_TEXTURE_2D", &texture2D))
				SetState(capability, texture2D);

			capability = GL_LINE_SMOOTH;
			bool lineSmooth = glIsEnabled(capability);
			if (ImGui::Checkbox("GL_LINE_SMOOTH", &lineSmooth))
				SetState(capability, lineSmooth);

			capability = GL_BLEND;
			bool blend = glIsEnabled(capability);
			if (ImGui::Checkbox("GL_BLEND", &blend))
				SetState(capability, blend);

			bool wireframeMode = false;
			GLint polygonMode[2];
			glGetIntegerv(GL_POLYGON_MODE, polygonMode);

			if (polygonMode[0] == GL_LINE && polygonMode[1] == GL_LINE)
				wireframeMode = true;
			if (ImGui::Checkbox("Wireframe", &wireframeMode))
			{
				if (wireframeMode)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

		}
		/*if (ImGui::CollapsingHeader("File System"))
		{
			ImGui::Text("Base Path:");
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%s", );
			ImGui::Text("Read Paths:");
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%s", );
			ImGui::Text("Write Path:");
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%s", );
		}*/
		if (ImGui::CollapsingHeader("Input"))
		{
			ImGui::Text("Mouse Position:");
			ImGui::SameLine();
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%i, %i", App->input->GetMouseX(), App->input->GetMouseY());

			ImGui::Text("Mouse Motion:");
			ImGui::SameLine();
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%i, %i", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());

			ImGui::Text("Mouse Wheel:");
			ImGui::SameLine();
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%i", App->input->GetMouseZ());

			ImGui::Separator();

			ImGuiWindowFlags scrollFlags = 0;
			scrollFlags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;

			ImGuiTextBuffer buf;

			if (ImGui::BeginChild("scroll", ImVec2(0, 0), false, scrollFlags))
			{
				ImGui::TextUnformatted(buf.begin());
				ImGui::SetScrollHere(1.0f);
			}
			ImGui::EndChild();
		}
		if (ImGui::CollapsingHeader("Hardware"))
		{

			SDL_version current;
			SDL_VERSION(&current);
			char nameChar[25];
			sprintf_s(nameChar, 25, "%d.%d.%d", current.major, current.minor, current.patch);
			ImGui::Text("SDL Version:");
			ImGui::SameLine();
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, nameChar);

			ImGui::Separator();

			ImGui::Text("CPUs:");
			ImGui::SameLine();
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%i (Cache: %ikb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());

			ImGui::Text("System RAM:");
			ImGui::SameLine();
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%.2fGB", (float)SDL_GetSystemRAM() / 1024);

			ImGui::Text("Caps:"); ImGui::SameLine();
			std::string caps("");
			if (SDL_Has3DNow())
				caps += "3Dnow, ";
			if (SDL_HasAVX())
				caps += "AVX, ";
			if (SDL_HasAVX2())
				caps += "AVX2, ";
			if (SDL_HasAltiVec())
				caps += "AltiVec, ";
			if (SDL_HasMMX())
				caps += "MMX, ";
			if (SDL_HasRDTSC())
				caps += "RDTSC , ";
			if (SDL_HasSSE())
				caps += "SSE, ";
			if (SDL_HasSSE2())
				caps += "SSE2, ";
			if (SDL_HasSSE3())
				caps += "SSE3, ";
			if (SDL_HasSSE41())
				caps += "SSE4.1, ";
			if (SDL_HasSSE42())
				caps += "SSE4.2, ";

			caps = caps.substr(0, caps.size() - 2);
			ImGui::SameLine();
			ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, caps.data());

			ImGui::Separator();

			ImGui::Text("GPU:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_VENDOR));

			ImGui::Text("Brand:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", glGetString(GL_RENDERER));

			GLint vram_budget;
			GLint vram_usage = 0;
			GLint vram_reserved = 0;
			GLint vram_available = 0;

			glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &vram_budget);
			ImGui::Text("VRAM Budget:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1f Mb", (vram_budget * 0.001));

			glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &vram_available);
			ImGui::Text("VRAM Available:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1f Mb", (vram_available * 0.001));



			glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &vram_reserved);
			ImGui::Text("VRAM Reserved:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1f Mb", (vram_reserved * 0.001));

			vram_usage = vram_budget - vram_available;

			ImGui::Text("VRAM Usage:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1f Mb", (vram_usage * 0.001));
		}
		if (ImGui::CollapsingHeader("Style"))
		{
			ImGui::ShowStyleSelector("Style##Selector");
		}
	}
	ImGui::End();
}

void ImGuiConfig::SetState(GLenum capability, bool enable) const
{
	if (glIsEnabled(capability))
	{
		if (!enable)
			glDisable(capability);
	}
	else
	{
		if (enable)
			glEnable(capability);
	}
}