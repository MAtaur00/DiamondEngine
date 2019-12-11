#include "ComponentBillboard.h"
#include "Application.h"

ComponentBillboard::ComponentBillboard(GameObject* parent): Component(parent, CompBillboard)
{

}

ComponentBillboard::~ComponentBillboard()
{

}

void ComponentBillboard::Inspector()
{

	if (ImGui::CollapsingHeader("Billboard"))
	{
		ImGui::Text("Billboard:");
		
		
		if (ImGui::BeginMenu("Sekect billboard"))
		{
			if(ImGui::MenuItem("Screen")) {
				billboardtype = BillboardScreen;

			}
			if(ImGui::MenuItem("Wold")) {
				billboardtype = BillboardWorld;

			}
			if(ImGui::MenuItem("Axially")) {
				billboardtype = BillboardAxially;

			}


		}


	}


}

void ComponentBillboard::Update()
{

}
