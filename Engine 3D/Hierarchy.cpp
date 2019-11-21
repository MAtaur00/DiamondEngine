#include "Hierarchy.h"
#include "Application.h"


Hierarchy::Hierarchy()
{
}


Hierarchy::~Hierarchy()
{
}

void Hierarchy::Draw()
{
	if (ImGui::Begin("Hierarchy", &App->imgui->showHierarchy, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoMove))
	{
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("New Game Object"))
			{
				GameObject* newGO = new GameObject(App->game_object->root);
			}
			ImGui::MenuItem("Cancel");
			ImGui::EndMenu();
		}
		

		if (App->game_object->root)
		{
			DrawGameObjects(App->game_object->root);
		}
	}
	ImGui::End();
}

void Hierarchy::DrawGameObjects(GameObject* current)
{
	uint flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;

	if (current->childs.size() == 0)
		flags |= ImGuiTreeNodeFlags_Leaf;

	if (current == App->sceneIntro->current_object)
		flags |= ImGuiTreeNodeFlags_Selected;

	char name[256];

	sprintf_s(name, 256, "%s##%u", current->name.c_str(), current->uuid);

	if (ImGui::TreeNodeEx(name, flags))
	{
		if (ImGui::IsItemClicked(0))
		{
			App->sceneIntro->current_object = current;
		}

		for (std::list<GameObject*>::iterator childs = current->childs.begin(); childs != current->childs.end(); ++childs)
		{
			DrawGameObjects(*childs);
		}
		ImGui::TreePop();
	}
}
