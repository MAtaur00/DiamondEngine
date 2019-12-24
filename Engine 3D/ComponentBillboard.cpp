#include "ComponentBillboard.h"
#include "Application.h"

ComponentBillboard::ComponentBillboard(GameObject* parent): Component(parent, CompBillboard)
{
	parent->components.push_back(this);
}

ComponentBillboard::~ComponentBillboard()
{
	gameObject->components.remove(this);
}

void ComponentBillboard::Inspector()
{
	if (ImGui::CollapsingHeader("Billboard"))
	{
		if (ImGui::BeginMenu("Select billboard"))
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
			ImGui::EndMenu();
		}

		if (billboardtype == BillboardAxially) 
		{
			if (ImGui::BeginMenu("Choose Axis"))
			{
				if (ImGui::MenuItem("X")) {
					billboardaxis = BillboardX;
				}
				if (ImGui::MenuItem("Y")) {
					billboardaxis = BillboardY;
				}
				if (ImGui::MenuItem("Z")) {
					billboardaxis = BillboardZ;
				}
				ImGui::EndMenu();
			}
		}
	}
}

void ComponentBillboard::Update()
{

	if (billboardtype != BillboardNone) {

		float3 x, y, z;

		switch (billboardtype)
		{

		case BillboardScreen:

			z = -App->renderer3D->current_cam->frustum.front;
			y = App->renderer3D->current_cam->frustum.up;

			x = y.Cross(z);

			break;

		case BillboardWorld:

			z = (App->renderer3D->current_cam->gameObject->transform->GetGlobalPos() - gameObject->transform->GetGlobalPos()).Normalized();
			y = App->renderer3D->current_cam->frustum.up;

			x = y.Cross(z);

			y = z.Cross(x);

			break;

		case BillboardAxially:

			float3 dist = (App->renderer3D->current_cam->gameObject->transform->GetGlobalPos() - gameObject->transform->GetGlobalPos()).Normalized();
			switch (billboardaxis) {

			case BillboardZ:

				z = gameObject->transform->GetGlobalRotation() * float3(0, 0, 1);
				y = z.Cross(dist);

				x = y.Cross(z);

				break;
			case BillboardY:

				y = gameObject->transform->GetGlobalRotation() * float3(0, 1, 0);
				x = y.Cross(dist);

				z = x.Cross(y);

				break;
			case BillboardX:

				x = gameObject->transform->GetGlobalRotation() * float3(1, 0, 0);
				y = dist.Cross(x);

				z = x.Cross(y);

				break;
			}
		}
	}
}