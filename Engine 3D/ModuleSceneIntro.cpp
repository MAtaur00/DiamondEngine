#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "MathGeoLib/MathGeoLib.h"
#include "Glew/include/glew.h"


#pragma comment(lib, "Glew/libx86/glew32.lib")

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	ImGuizmo::Enable(true);
	quadtree.QT_Create(AABB(float3(-60, -5, -60), float3(60, 10, 60)));
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
	{
		guiz_operation = ImGuizmo::BOUNDS;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
	{
		guiz_operation = ImGuizmo::TRANSLATE;
	}
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		guiz_operation = ImGuizmo::SCALE;
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		guiz_operation = ImGuizmo::ROTATE;
	}

	if (current_object)
	{
		float4x4 transformGlobal = current_object->transform->GetMatrix();
		transformGlobal.Transpose();

		ImGuiIO& io = ImGui::GetIO();

		ImGuizmo::SetRect(0.f, 0.f, io.DisplaySize.x, io.DisplaySize.y);

		ImGuizmo::Manipulate(App->renderer3D->current_cam->GetViewMatrix().ptr(), App->renderer3D->current_cam->GetProjectionMatrix().ptr(), guiz_operation, guiz_mode, transformGlobal.ptr(), nullptr, nullptr);

		if (ImGuizmo::IsUsing() && Time::gameState == GameState::EDITOR)
		{
			transformGlobal.Transpose();
			if (current_object->parent)
			{
				float4x4 matrix = current_object->parent->transform->GetMatrix();
				matrix.Inverse();
				transformGlobal = matrix.Mul(transformGlobal);
			}
			float3 pos, scale;
			Quat rot;
			transformGlobal.Decompose(pos, rot, scale);
			switch (guiz_operation)
			{
			case ImGuizmo::TRANSLATE:
				current_object->transform->SetPos(pos);
				break;
			case ImGuizmo::ROTATE:
				current_object->transform->SetRotation(rot);
				break;
			case ImGuizmo::SCALE:
				current_object->transform->SetScale(scale);
				break;
			default:
				break;
			}
		}
	}



	PrimitivePlane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::ReDoQuadtree()
{

	quadtree.QT_Create(AABB(float3(-60, -5, -60), float3(60, 10, 60)));

	for (std::list<GameObject*>::const_iterator iterator = App->game_object->gameObjects.begin(); iterator != App->game_object->gameObjects.end(); ++iterator)
	{
		if ((*iterator)->HasComponent(CompMesh))
			quadtree.QT_Insert((*iterator));
	}
}