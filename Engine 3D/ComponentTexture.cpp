#include "ComponentTexture.h"



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
		ImGui::Text("%s", path.c_str());
		ImGui::Image((void*)(intptr_t)tex_id, ImVec2(225,225), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
	}
}
