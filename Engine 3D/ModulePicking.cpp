#include "ModulePicking.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleGameObject.h"


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
		if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LALT) != KEY_REPEAT)
		{
			float mouseX = -(1.f - ((float(App->input->GetMouseX()) * 2.f) / (float)App->window->width));
			float mouseY = (1.f - ((float(App->input->GetMouseY()) * 2.f) / (float)App->window->height));

			LineSegment picking = App->camera->compCamera->frustum.UnProjectLineSegment(mouseX, mouseY);

			float smallerDist = -1.0f;

			GameObject* closestObject = nullptr;

			for (std::list<GameObject*>::iterator it = App->game_object->gameObjects.begin(); it != App->game_object->gameObjects.end(); ++it)
			{
				if ((*it)->active)
				{
					LineSegment ray(picking);
					ray.Transform((*it)->transform->GetMatrix().Inverted());

					ComponentMesh* mesh = (ComponentMesh*)(*it)->GetComponent(Object_Type::CompMesh);
					if (mesh)
					{
						Triangle triangle;
						for (int i = 0; i < mesh->mesh->index.size / 3; ++i)
						{
							triangle.a.x = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3] * 3];
							triangle.a.y = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3] * 3 + 1];
							triangle.a.z = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3] * 3 + 2];

							triangle.b.x = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3 + 1] * 3];
							triangle.b.y = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3 + 1] * 3 + 1];
							triangle.b.z = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3 + 1] * 3 + 2];

							triangle.c.x = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3 + 2] * 3];
							triangle.c.y = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3 + 2] * 3 + 1];
							triangle.c.z = mesh->mesh->vertex.data[mesh->mesh->index.data[i * 3 + 2] * 3 + 2];

							float distance;
							float3 position;

							if (ray.Intersects(triangle, &distance, &position))
							{
								if (distance < smallerDist || smallerDist == -1.0f)
								{
									smallerDist = distance;
									closestObject = (*it);
								}
							}
						}
					}
				}
			}
			App->sceneIntro->current_object = closestObject;
		}
	}
	return UPDATE_CONTINUE;
}