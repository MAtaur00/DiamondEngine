#include "Inspector.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

Inspector::Inspector()
{
}

Inspector::~Inspector()
{
}

void Inspector::Draw()
{
	if (ImGui::Begin("Inspector", &App->imgui->showInspector, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove))
	{
		ImGui::SetWindowPos(ImVec2((App->window->width / 10.0f) * 8.0f, 18), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2((App->window->width / 10.0f) * 2.0f, (App->window->height) / 6.0f * 4.5f), ImGuiCond_Always);
		if (App->sceneIntro->current_object)
		{
			char buf[64];
			strcpy_s(buf, 64, App->sceneIntro->current_object->name.c_str());
			if (ImGui::InputText("##Name", buf, IM_ARRAYSIZE(buf)))
			{
				App->sceneIntro->current_object->name = buf;
			}

			ImGui::Checkbox("Active", &App->sceneIntro->current_object->active);

			App->sceneIntro->current_object->transform->Inspector();
			for (std::list<Component*>::iterator it = App->sceneIntro->current_object->components.begin(); it != App->sceneIntro->current_object->components.end(); ++it)
			{
				(*it)->Inspector();
			}
		}

		if (ImGui::BeginMenu("New Component"))
		{
			if (ImGui::MenuItem("Mesh"))
			{
				
			}
			if (ImGui::MenuItem("Texture"))
			{

			}
			if (ImGui::MenuItem("Camera"))
			{
				ComponentCamera* camera = new ComponentCamera(App->sceneIntro->current_object);
				App->renderer3D->play_cam = camera;
			}
			ImGui::MenuItem("Cancel");
			ImGui::EndMenu();
		}
		
	}
	ImGui::End();
}