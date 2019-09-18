#include "ModuleIMGui.h"
#include "ModuleWindow.h"
#include "Application.h"
#include "imgui-1.72b/imgui_impl_sdl.h"
#include "imgui-1.72b/imgui_impl_opengl2.h"
#include "imgui-1.72b/imgui_internal.h"
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

	IMGUI_CHECKVERSION();
	CreateContext();
	ImGuiIO& io = GetIO();
	(void)io;
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL2_Init();
	StyleColorsDark();

	return ret;
}

update_status ModuleIMGui::PreUpdate(float dt)
{
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	NewFrame();
	bool showDemo = true;
	ShowDemoWindow(&showDemo);

	return update_status::UPDATE_CONTINUE;
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