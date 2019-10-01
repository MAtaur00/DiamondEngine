#include "ModuleIMGui.h"
#include "ModuleWindow.h"
#include "Application.h"
#include "Glew/include/glew.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "MathGeoLib/MathGeoLib.h"
#include "pcg/pcg_basic.h"
#include "Psapi.h"
#include "Windows.h"



using namespace ImGui;


                          
ModuleIMGui::ModuleIMGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleIMGui::~ModuleIMGui()
{
}

bool ModuleIMGui::Start()
{
	bool ret = true;

	

	return ret;
}

update_status ModuleIMGui::PreUpdate(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	ImGui_ImplOpenGL3_NewFrame();

	ImGui_ImplSDL2_NewFrame(App->window->window);
	NewFrame();

	if (BeginMainMenuBar())
	{
		if (BeginMenu("File"))
		{
			if (MenuItem("Save"))
			{
				
			}
			if (MenuItem("Load"))
			{
				
			}
			ImGui::Separator();
			if (MenuItem("Quit"))
			{
				ret = UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		if (BeginMenu("View"))
		{
			if (MenuItem("Configuration"))
			{
				showConfiguration = !showConfiguration;
			}
			if (MenuItem("Console"))
			{
				showConsole = !showConsole;
			}
			if (MenuItem("MathGeoLib"))
			{
				showMath = !showMath;
			}
			else if (MenuItem("PCG"))
			{
				showRNG = !showRNG;
			}
			ImGui::EndMenu();
		}
		if (BeginMenu("Help"))
		{
			if (MenuItem("Show Demo Window"))
				showDemo = !showDemo;
			if (MenuItem("Documentation"))
				ShellExecuteA(NULL, "Open", "https://github.com/MAtaur00/DiamondEngine/wiki", NULL, NULL, SW_SHOWNORMAL);
			if (MenuItem("Download latest"))
				ShellExecuteA(NULL, "Open", "https://github.com/MAtaur00/DiamondEngine/releases", NULL, NULL, SW_SHOWNORMAL);
			if (MenuItem("Report bug"))
				ShellExecuteA(NULL, "Open", "https://github.com/MAtaur00/DiamondEngine/issues", NULL, NULL, SW_SHOWNORMAL);
			if (MenuItem("About"))
				showAbout = !showAbout;

			ImGui::EndMenu();
		}
		EndMainMenuBar();
	}
	if (showDemo)
		ShowDemoWindow(&showDemo);
	if (showMath)
	{
		if (ImGui::Begin("MathGeoLib", &showMath))
		{
			const char* listbox_items[] = { "Sphere", "Capsule", "AABB", "OBB", "Ray", "Triangle" };
			ImGui::Text("Object 1");
			ImGui::ListBox("##Object1", &current_object1, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			ImGui::NewLine();
			ImGui::Text("Object 2");
			ImGui::ListBox("##Object2", &current_object2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
			
			ImGui::NewLine();
			ImGui::Text("Move the sliders to move the objects");
			ImGui::NewLine();
			ImGui::SliderFloat("Object 1", &posx1, 0.0f, 5.0f, "%.1f");
			ImGui::SliderFloat("Object 2", &posx2, 0.0f, 5.0f, "%.1f");
			

			ImGui::NewLine();
			
			bool colliding = false;
			switch (current_object1)
			{
			case Type_Sphere:
			{
				Sphere sph1({ posx1, 0.0f, 0.0f }, 1.f);
				switch (current_object2)
				{
				case Type_Sphere:
				{
					Sphere sph2({ posx2, 0.0f, 0.0f }, 1.f);
					colliding = sph1.Intersects(sph2);
					break;
				}
				case Type_Capsule:
				{
					Capsule cap2({ posx2, 0.0f, -1.0f }, { posx2, 0.0f, 1.0f }, 1.f);
					colliding = sph1.Intersects(cap2);
					break;
				}
				case Type_AABB:
				{
					AABB aabb2({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					colliding = sph1.Intersects(aabb2);
					break;
				}
				case Type_OBB:
				{
					AABB aabb3({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					OBB obb2(aabb3);
					colliding = sph1.Intersects(obb2);
					break;
				}
				case Type_Ray:
				{
					Ray ray2({ posx2, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
					colliding = sph1.Intersects(ray2);
					break;
				}
				case Type_Triangle:
				{
					Triangle tri2({ posx2, 0.0f, 0.5f }, { posx2, 0.5f, -0.5f }, { posx2, -0.5f, -0.5f });
					colliding = sph1.Intersects(tri2);
					break;
				}
				default:
					break;
				}
				break;
			}
			case Type_Capsule:
			{
				Capsule cap1({ posx1, 0.0f, -1.0f }, { posx1, 0.0f, 1.0f }, 1.f);
				switch (current_object2)
				{
				case Type_Sphere:
				{
					Sphere sph2({ posx2, 0.0f, 0.0f }, 1.f);
					colliding = cap1.Intersects(sph2);
					break;
				}
				case Type_Capsule:
				{
					Capsule cap2({ posx2, 0.0f, -1.0f }, { posx2, 0.0f, 1.0f }, 1.f);
					colliding = cap1.Intersects(cap2);
					break;
				}
				case Type_AABB:
				{
					AABB aabb2({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					colliding = cap1.Intersects(aabb2);
					break;
				}
				case Type_OBB:
				{
					AABB aabb3({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					OBB obb2(aabb3);
					colliding = cap1.Intersects(obb2);
					break;
				}
				case Type_Ray:
				{
					Ray ray2({ posx2, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
					colliding = cap1.Intersects(ray2);
					break;
				}
				case Type_Triangle:
				{
					Triangle tri2({ posx2, 0.0f, 0.5f }, { posx2, 0.5f, -0.5f }, { posx2, -0.5f, -0.5f });
					colliding = cap1.Intersects(tri2);
					break;
				}
				default:
					break;
				}
				break;
			}
			case Type_AABB:
			{
				AABB aabb1({ posx1, -1.0f, -1.0f }, { posx1, 1.0f, 1.0f });
				switch (current_object2)
				{
				case Type_Sphere:
				{
					Sphere sph2({ posx2, 0.0f, 0.0f }, 1.f);
					colliding = aabb1.Intersects(sph2);
					break;
				}

				case Type_Capsule:
				{
					Capsule cap2({ posx2, 0.0f, -1.0f }, { posx2, 0.0f, 1.0f }, 1.f);
					colliding = aabb1.Intersects(cap2);
					break;
				}
				case Type_AABB:
				{
					AABB aabb2({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					colliding = aabb1.Intersects(aabb2);
					break;
				}
				case Type_OBB:
				{
					AABB aabb3({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					OBB obb2(aabb3);
					colliding = aabb1.Intersects(obb2);
					break;
				}
				case Type_Ray:
				{
					Ray ray2({ posx2, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
					colliding = aabb1.Intersects(ray2);
					break;
				}
				case Type_Triangle:
				{
					Triangle tri2({ posx2, 0.0f, 0.5f }, { posx2, 0.5f, -0.5f }, { posx2, -0.5f, -0.5f });
					colliding = aabb1.Intersects(tri2);
					break;
				}
				default:
					break;
				}
				break;
			}
			case Type_OBB:
			{
				AABB aabb4({ posx1, -1.0f, -1.0f }, { posx1, 1.0f, 1.0f });
				OBB obb1(aabb4);
				switch (current_object2)
				{
				case Type_Sphere:
				{
					Sphere sph2({ posx2, 0.0f, 0.0f }, 1.f);
					colliding = obb1.Intersects(sph2);
					break;
				}
				case Type_Capsule:
				{
					Capsule cap2({ posx2, 0.0f, -1.0f }, { posx2, 0.0f, 1.0f }, 1.f);
					colliding = obb1.Intersects(cap2);
					break;
				}
				case Type_AABB:
				{
					AABB aabb2({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					colliding = obb1.Intersects(aabb2);
					break;
				}
				case Type_OBB:
				{
					AABB aabb3({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					OBB obb2(aabb3);
					colliding = obb1.Intersects(obb2);
					break;
				}

				case Type_Ray:
				{
					Ray ray2({ posx2, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
					colliding = obb1.Intersects(ray2);
					break;
				}
				case Type_Triangle:
				{
					Triangle tri2({ posx2, 0.0f, 0.5f }, { posx2, 0.5f, -0.5f }, { posx2, -0.5f, -0.5f });
					colliding = obb1.Intersects(tri2);
					break;
				}
				default:
					break;
				}
				break;
			}
			case Type_Ray:
			{
				Ray ray1({ posx1, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
				switch (current_object2)
				{
				case Type_Sphere:
				{
					Sphere sph2({ posx2, 0.0f, 0.0f }, 1.f);
					colliding = ray1.Intersects(sph2);
					break;
				}
				case Type_Capsule:
				{
					Capsule cap2({ posx2, 0.0f, -1.0f }, { posx2, 0.0f, 1.0f }, 1.f);
					colliding = ray1.Intersects(cap2);
					break;
				}
				case Type_AABB:
				{
					AABB aabb2({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					colliding = ray1.Intersects(aabb2);
					break;
				}
				case Type_OBB:
				{
					AABB aabb3({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					OBB obb2(aabb3);
					colliding = ray1.Intersects(obb2);
					break;
				}
				/*case Type_Ray:
				{
					Ray ray2({ posx2, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
					colliding = ray1.Intersects(ray2);
					break;
				}*/
				case Type_Triangle:
				{
					Triangle tri2({ posx2, 0.0f, 0.5f }, { posx2, 0.5f, -0.5f }, { posx2, -0.5f, -0.5f });
					colliding = ray1.Intersects(tri2);
					break;
				}
				default:
					break;
				}
				break;
			}
			case Type_Triangle:
			{
				Triangle tri1({ posx1, 0.0f, 0.5f }, { posx1, 0.5f, -0.5f }, { posx1, -0.5f, -0.5f });
				switch (current_object2)
				{
				case Type_Sphere:
				{
					Sphere sph2({ posx2, 0.0f, 0.0f }, 1.f);
					colliding = tri1.Intersects(sph2);
					break;
				}
				case Type_Capsule:
				{
					Capsule cap2({ posx2, 0.0f, -1.0f }, { posx2, 0.0f, 1.0f }, 1.f);
					colliding = tri1.Intersects(cap2);
					break;
				}
				case Type_AABB:
				{
					AABB aabb2({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					colliding = tri1.Intersects(aabb2);
					break;
				}
				case Type_OBB:
				{
					AABB aabb3({ posx2, -1.0f, -1.0f }, { posx2, 1.0f, 1.0f });
					OBB obb2(aabb3);
					colliding = tri1.Intersects(obb2);
					break;
				}
				case Type_Ray:
				{
					Ray ray2({ posx2, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f });
					colliding = tri1.Intersects(ray2);
					break;
				}
				case Type_Triangle:
				{
					Triangle tri2({ posx2, 0.0f, 0.5f }, { posx2, 0.5f, -0.5f }, { posx2, -0.5f, -0.5f });
					colliding = tri1.Intersects(tri2);
					break;
				}
				default:
					break;
				}
				break;
			}
			default:
				break;
			}

			if (colliding)
			{
				ImGui::Text("The objects are colliding");
			}
			else
				ImGui::Text("The objects are not colliding");
		}
		ImGui::End();
	}

	if (showRNG)
	{
		if (ImGui::Begin("PCG", &showRNG))
		{
			if (ImGui::Button("Generate random float"))
			{
				randomFloat = (float)pcg32_random() / MAXUINT;
			}
			ImGui::Text("Generated float: %.2f", randomFloat);
			ImGui::DragInt2("Min number", buttonMinMax, 1, -MAXINT, MAXINT);
			if (ImGui::Button("Generate random int"))
			{
				randomInt = ((float)pcg32_random() / MAXUINT) * buttonMinMax[1] + buttonMinMax[0];
			}
			ImGui::Text("Generated int: %i", randomInt);
		}
		ImGui::End();
	}

	if (showConfiguration)
	{
		if (ImGui::Begin("Configuration", &showConfiguration))
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

				sprintf_s(title, 25, "Memory Consumption %.1f", ram_log[ram_log.size() - 1]);
				ImGui::PlotHistogram("##memory consumption", &ram_log[0], ram_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));



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

				if (ImGui::SliderFloat("Brightness", &brightnessPos, 0.0f, 1.0f))
				{
					SDL_SetWindowBrightness(App->window->window, brightnessPos);
				}
				if (ImGui::SliderInt("Width", &widthPos, 640, 1920))
				{
					SDL_SetWindowSize(App->window->window, widthPos, heightPos);
					App->renderer3D->OnResize(widthPos, heightPos);
				}
				if (ImGui::SliderInt("Height", &heightPos, 480, 1080))
				{
					SDL_SetWindowSize(App->window->window, widthPos, heightPos);
					App->renderer3D->OnResize(widthPos, heightPos);
				}

				if (ImGui::Checkbox("Fullscreen", &fullscreen))
				{
					App->window->SetFullscreen(fullscreen);
				}
					
				ImGui::SameLine();

				if (ImGui::Checkbox("Resizable", &resizable))
				{
					App->window->SetResizable(resizable);
				}

				if (ImGui::Checkbox("Borderless", &borderless))
				{
					App->window->SetBorderless(borderless);
				}

				ImGui::SameLine();

				if (ImGui::Checkbox("Full Desktop", &fullDesktop))
				{
					App->window->SetFullDesktop(fullDesktop);
				}

				if (ImGui::IsItemHovered)
				{
					ImGui::SetTooltip("Restart to apply");
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
				ImGui::TextColored({ 1.f, 1.f, 0, 1.f }, "%.2fGB", (float)SDL_GetSystemRAM()/1024);

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
		}
		ImGui::End();
	}
	if (showConsole)
	{
		if (ImGui::Begin("Console", &showConsole))
		{

		}
		ImGui::End();
	}
	if (showAbout)
	{
		if (ImGui::Begin("About"), &showAbout)
		{
			ImGui::Separator();
			ImGui::TextWrapped("MIT License Copyright (c) 2019 Marc Tarrés and Aleix Castillo"

				"Permission is hereby granted, free of charge, to any person obtaining a copy of this software"
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

	return ret;
}

update_status ModuleIMGui::PostUpdate(float dt)
{
	PROCESS_MEMORY_COUNTERS counters;
	GetProcessMemoryInfo(GetCurrentProcess(), &counters, sizeof(counters));

	float ramInUse = counters.WorkingSetSize;
	ramInUse /= 1024;
	ramInUse /= 1024;

	ram_log.push_back(ramInUse);
	if (ram_log.size() > 75)
	{
		ram_log.erase(ram_log.begin());
	}

	return update_status::UPDATE_CONTINUE;
}

bool ModuleIMGui::CleanUp()
{
	return true;
}

void ModuleIMGui::Draw()
{
	Render();
	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}