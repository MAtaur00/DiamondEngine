#include "ComponentTexture.h"
#include "Application.h"
#include "ModuleImport.h"

ComponentTexture::ComponentTexture(GameObject* parent) : Component(parent, CompTexture)
{
	parent->components.push_back(this);
}


ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::Inspector()
{
	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Checkbox("Active", &print);
		ImGui::Text("%s", path.c_str());
		ImGui::Image((void*)(intptr_t)RTexture->id, ImVec2(225,225), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
		ImGui::Checkbox("Checkers", &checkers);
	}
}

unsigned int ComponentTexture::GetID()
{
	return checkers == false ? RTexture->id : App->import->checkerImageID;
}
