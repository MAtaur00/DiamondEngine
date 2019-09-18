#include "ModuleIMGui.h"
#include "ModuleWindow.h"
#include "Application.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "imgui_internal.h"
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

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	NewFrame();

	if (BeginMainMenuBar())
	{
		if (BeginMenu("Menu"))
		{
			if (MenuItem("Show Demo Window"))
			{
				showDemo = !showDemo;
			}
			else if (MenuItem("Exit"))
			{
				ret = UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		EndMainMenuBar();
	}
	if (showDemo)
		ShowDemoWindow(&showDemo);

	return ret;
}

update_status ModuleIMGui::PostUpdate(float dt)
{
	Render();
	ImGui_ImplOpenGL2_RenderDrawData(GetDrawData());

	return update_status::UPDATE_CONTINUE;
}

bool ModuleIMGui::CleanUp()
{
	return true;
}

void ModuleIMGui::Draw()
{

}