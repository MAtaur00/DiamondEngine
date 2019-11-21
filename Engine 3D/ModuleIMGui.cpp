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
#include "ImGuiConfig.h"
#include "ImGuiConsole.h"
#include "ImGuiAbout.h"
#include "Hierarchy.h"
#include "Inspector.h"
#include "Shapes.h"

using namespace ImGui;
                          
ModuleIMGui::ModuleIMGui(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	gui_config = new ImGuiConfig;
	gui_about = new ImGuiAbout;
	gui_console = new ImGuiConsole;
	hierarchy = new Hierarchy;
	inspector = new Inspector;
}


ModuleIMGui::~ModuleIMGui()
{
}

update_status ModuleIMGui::PreUpdate()
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
				saveScenePopup = true;
			}
			if (MenuItem("Load"))
			{
				loadScenePopup = true;
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
			if (MenuItem("PCG"))
			{
				showRNG = !showRNG;
			}
			if (MenuItem("Hierarchy"))
			{
				showHierarchy = !showHierarchy;
			}
			if (MenuItem("Inspector"))
			{
				showInspector = !showInspector;
			}
			if (MenuItem("Shapes"))
			{
				showShapes = !showShapes;
			}
			if (MenuItem("Show Demo Window"))
				showDemo = !showDemo;
			if (MenuItem("Camera"))
				showCamera = !showCamera;
			ImGui::EndMenu();
		}
		if (BeginMenu("Help"))
		{		
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
		gui_config->Draw();
		
	}
	if (showConsole)
	{		
		gui_console->Draw();
	}
	if (showAbout)
	{
		gui_about->Draw();
	}
	if (showHierarchy)
	{
		hierarchy->Draw();
	}
	if (showInspector)
	{
		inspector->Draw();
	}
	if (showShapes)
	{
		shapes->Draw();
	}
	if (showCamera)
	{
		ImGui::Begin("Camera", &App->imgui->showCamera);

		App->camera->compCamera->Inspector();

		ImGui::End();
	}

	if (saveScenePopup)
	{
		ImGui::OpenPopup("Save Scene Here");
		saveScenePopup = false;
	}

	if (ImGui::BeginPopup("Save Scene Here", ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		char buf[64];
		sprintf_s(buf, 64, lastSceneName.data());
		if (ImGui::InputText("Scene Name", buf, IM_ARRAYSIZE(buf)))
		{
			lastSceneName = buf;
		}

		ImGui::SameLine();

		if (ImGui::Button("SAVE"))
		{
			App->game_object->SaveScene(lastSceneName.data());

			ImGui::CloseCurrentPopup();
		}

		if (ImGui::Button("CANCEL"))
		{
			lastSceneName = "Scene";
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (loadScenePopup)
	{
		ImGui::OpenPopup("Load");
		loadScenePopup = false;
	}

	if (ImGui::BeginPopup("Load"))
	{
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Drag the scene file to load");
		ImGui::EndPopup();
	}

	return ret;
}

update_status ModuleIMGui::PostUpdate()
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