#include "ModulePicking.h"
#include "Application.h"
#include "ModuleWindow.h"


ModulePicking::ModulePicking(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModulePicking::~ModulePicking()
{
}

update_status ModulePicking::Update(float dt)
{
	if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
	{
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT)
		{
			float mouseX = -(1.f - ((float(App->input->GetMouseX()) * 2.f) / (float)App->window->width));
			float mouseY = (1.f - ((float(App->input->GetMouseY()) * 2.f) / (float)App->window->height));

			LineSegment ray = App->camera->frustum.UnProjectLineSegment(mouseX, mouseY);
		}
	}

	return update_status();
}
