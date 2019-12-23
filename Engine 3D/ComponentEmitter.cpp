#include "ComponentEmitter.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleParticleManager.h"
#include "Particle.h"
#include "ModuleTime.h"
#include "ResourceTexture.h"

ComponentEmitter::ComponentEmitter(GameObject* parent) : Component(parent, CompEmitter)
{
	parent->components.push_back(this);
	App->particle_manager->emitters.push_back(this);
}

ComponentEmitter::~ComponentEmitter()
{
}

void ComponentEmitter::Inspector()
{
	if (ImGui::CollapsingHeader("Particle Emitter", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat("Speed", &speed, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (ImGui::DragFloat("Rotation##Particles", &rotation, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (ImGui::DragFloat("Size", &size, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (ImGui::DragFloat("Ratio", &ratio, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (texture)
		{
			ImGui::Text("%s", texPath.c_str());
			ImGui::Image((void*)(intptr_t)texture->id, ImVec2(225, 225), ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));
		}

		ImGui::Separator();

		ImGui::ColorPicker4("Color", &color.x);

		ImGui::Separator();

		if (ImGui::Button("Reset##Particles"))
		{
			speed = 1.0f;
			rotation = 0.0f;
			size = 1.0f;
			ratio = 0.0f;
		}

		if (ImGui::Button("Delete Emitter"))
		{
			App->game_object->componentsToDelete.push_back(this);
		}
	}
}

void ComponentEmitter::Update()
{
	float time = timer.Read();

	if (ratio > 0.0f)
	{
		if (time >= ratio)
		{
			if (App->module_time->gameState == GameState::PLAYING)
			{
				float3 up = float3::unitY;

				int pos = App->particle_manager->GetLastParticle();
				App->particle_manager->particles[pos].SetActive(position, speed, (float3::unitY * gameObject->transform->GetRotation().ToFloat3x3()).Normalized(), rotation, size, life, &texture, color);
				particlesList.push_back(&App->particle_manager->particles[pos]);
				App->particle_manager->particles[pos].emitterpart = this;
				App->particle_manager->activeParticles++;
			}
		}
	}
}

void ComponentEmitter::Save(JSON_Object * parent)
{
	json_object_set_number(parent, "Type", type);
	json_object_set_number(parent, "UUID", uuid);

	// Position
	//------------------------------------------------------------------------
	JSON_Value* pos = json_value_init_object();
	JSON_Object* positionObj = json_value_get_object(pos);

	json_object_set_value(parent, "Position", pos);

	json_object_set_number(positionObj, "X", position.x);
	json_object_set_number(positionObj, "Y", position.y);
	json_object_set_number(positionObj, "Z", position.z);

	// Speed
	//------------------------------------------------------------------------
	JSON_Value* sp = json_value_init_object();
	JSON_Object* speedObj = json_value_get_object(sp);

	json_object_set_value(parent, "Speed", sp);

	json_object_set_number(positionObj, "Value", speed);

	// Direction
	//------------------------------------------------------------------------
	JSON_Value* dir = json_value_init_object();
	JSON_Object* directionObj = json_value_get_object(dir);

	json_object_set_value(parent, "Direction", dir);

	json_object_set_number(positionObj, "X", direction.x);
	json_object_set_number(positionObj, "Y", direction.y);
	json_object_set_number(positionObj, "Z", direction.z);

	// Rotation
	//------------------------------------------------------------------------
	JSON_Value* rot = json_value_init_object();
	JSON_Object* roationObj = json_value_get_object(rot);

	json_object_set_value(parent, "Rotation", rot);

	json_object_set_number(positionObj, "Value", rotation);

	// Size
	//------------------------------------------------------------------------
	JSON_Value* siz = json_value_init_object();
	JSON_Object* sizeObj = json_value_get_object(siz);

	json_object_set_value(parent, "Size", siz);

	json_object_set_number(positionObj, "Value", size);

	// Texture Path
	//------------------------------------------------------------------------
	json_object_set_string(parent, "Path", texPath.c_str());

	// Color
	//------------------------------------------------------------------------
	JSON_Value* clr = json_value_init_object();
	JSON_Object* colorObj = json_value_get_object(clr);

	json_object_set_value(parent, "Color", clr);

	json_object_set_number(positionObj, "X", color.x);
	json_object_set_number(positionObj, "Y", color.y);
	json_object_set_number(positionObj, "Z", color.z);
	json_object_set_number(positionObj, "W", color.w);
}

void ComponentEmitter::Load(JSON_Object * parent)
{
	uuid = json_object_get_number(parent, "UUID");

	// Position
	//------------------------------------------------------------------------
	JSON_Object* pos = json_object_get_object(parent, "Position");
	position.x = json_object_get_number(pos, "X");
	position.y = json_object_get_number(pos, "Y");
	position.z = json_object_get_number(pos, "Z");

	// Speed
	//------------------------------------------------------------------------
	JSON_Object* sp = json_object_get_object(parent, "Speed");
	speed = json_object_get_number(sp, "ValueX");

	// Direction
	//------------------------------------------------------------------------
	JSON_Object* dir = json_object_get_object(parent, "Direction");
	direction.x = json_object_get_number(dir, "X");
	direction.y = json_object_get_number(dir, "Y");
	direction.z = json_object_get_number(dir, "Z");

	// Rotation
	//------------------------------------------------------------------------
	JSON_Object* rot = json_object_get_object(parent, "Rotation");
	rotation = json_object_get_number(rot, "Value");

	// Size
	//------------------------------------------------------------------------
	JSON_Object* siz = json_object_get_object(parent, "Size");
	size = json_object_get_number(siz, "Value");

	// Texture
	//------------------------------------------------------------------------
	texPath = json_object_get_string(parent, "Path");
	texture = new ResourceTexture(texPath.c_str());

	// Color
	//------------------------------------------------------------------------
	JSON_Object* clr = json_object_get_object(parent, "Color");
	color.x = json_object_get_number(clr, "X");
	color.y = json_object_get_number(clr, "Y");
	color.z = json_object_get_number(clr, "Z");
	color.w = json_object_get_number(clr, "W");
}