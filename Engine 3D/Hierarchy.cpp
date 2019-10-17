#include "Hierarchy.h"
#include "Application.h"


Hierarchy::Hierarchy()
{
}


Hierarchy::~Hierarchy()
{
}

bool Hierarchy::Start()
{
	bool ret = true;

	return ret;
}

void Hierarchy::Draw()
{
	if (ImGui::Begin("Hierarchy"), &App->imgui->showHierarchy)
	{
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

	char name[80];

	std::string sName = current->name;

	sprintf_s(name, 80, "%s", sName.c_str());

	if (ImGui::TreeNodeEx(name, flags))
	{
		if (ImGui::IsItemClicked(0))
		{
			App->sceneIntro->current_object = current;
		}

		for (std::list<GameObject*>::iterator childs = current->childs.begin(); childs != current->childs.end(); ++childs)
		{
			DrawGameObjects(*childs);

			//if (ImGui::IsItemClicked(1) && objectSelected == nullptr)
			//{
			//	objectSelected = *childs;
			//	popHierarchy = true;
			//}
		}
		ImGui::TreePop();
	}
}
