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
	if (ImGui::Begin("Inspector", &App->imgui->showInspector))
	{
		if (App->sceneIntro->current_object)
		{
			char buf[64];
			strcpy_s(buf, 64, App->sceneIntro->current_object->name.c_str());
			if (ImGui::InputText("##Name", buf, IM_ARRAYSIZE(buf)))
			{
				App->sceneIntro->current_object->name = buf;
			}

			App->sceneIntro->current_object->transform->Inspector();
		}
	}
	ImGui::End();
}