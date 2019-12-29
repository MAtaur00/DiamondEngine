#include "ComponentEmitter.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleParticleManager.h"
#include "Particle.h"
#include "ModuleTime.h"
#include "ResourceTexture.h"
#include "Inspector.h"

ComponentEmitter::ComponentEmitter(GameObject* parent) : Component(parent, CompEmitter)
{
	parent->components.push_back(this);
	App->particle_manager->emitters.push_back(this);
}

ComponentEmitter::~ComponentEmitter()
{
	App->particle_manager->emitters.remove(this);
}

bool ComponentEmitter::Start()
{
	timer.Start();
	timerBurst.Start();

	Clear();

	return true;
}

void ComponentEmitter::Inspector()
{
	if (ImGui::CollapsingHeader("Particle Emitter", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat("Speed", &speed, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (ImGui::DragFloat("Life", &life, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (ImGui::DragFloat3("Direction", &direction.x, 0.1f, 0.0f, 0.0f, "%.2f"))
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

		if (ImGui::DragFloat("Time between particles", &ratio, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (ImGui::DragFloat("Time between bursts", &burstRatio, 0.1f, 0.0f, 0.0f, "%.2f"))
		{
		}

		ImGui::Separator();

		if (ImGui::DragInt("Particles in burst", &particlesBurst, 1, 0, 100))
		{
		}

		ImGui::Separator();

		if (ImGui::RadioButton("Cone shape", shapeType == Cone_TYPE) )
		{
			shapeType = Cone_TYPE;
		}

		if (ImGui::RadioButton("Sphere shape", shapeType == Sphere_TYPE))
		{
			shapeType = Sphere_TYPE;
		}

		if (ImGui::RadioButton("Box shape", shapeType == Box_TYPE))
		{
			shapeType = Box_TYPE;
		}

		ImGui::Separator();

		switch (shapeType)
		{
		case Cone_TYPE:

			if (ImGui::DragFloat("Cone heigh", &heigh, 0.1f, 0.0f, 0.0f, "%.2f"))
			{
				circle.pos.y = heigh;

			}

			if (ImGui::DragFloat("Cone radius", &rad, 0.1f, 0.0f, 0.0f, "%.2f"))
			{
				circle.r = rad;

			}
			break;
		case Sphere_TYPE:
			if (ImGui::DragFloat("Sphere radius", &rad, 0.1f, 0.0f, 0.0f, "%.2f"))
			{
				sphere.r = rad;

			}
			break;
		case Box_TYPE:
			if (ImGui::DragFloat3("Box size", &boxSize.x, 0.1f, 0.0f, 0.0f, "%.2f"))
			{
				cube.SetFromCenterAndSize(gameObject->transform->GetGlobalPos(), boxSize);

			}
			break;
		default:
			break;
		}

		ImGui::Separator();

		ImGui::ColorPicker4("Color", &color.x);

		ImGui::Separator();

		ImGui::Checkbox("Subemitter", &subEmitter);

		ImGui::Separator();

		if (ImGui::Button("Reset##Particles"))
		{
			speed = 1.0f;
			rotation = 0.0f;
			size = 1.0f;
			ratio = 0.0f;
			life = 0.0f;
			burstRatio = 0.0f;
			particlesBurst = 0;
		}

		if (ImGui::Button("Delete Emitter"))
		{
			App->game_object->componentsToDelete.push_back(this);
		}
	}
}

void ComponentEmitter::Update()
{
	
	

	if (gameObject->HasComponent(CompTexture))
	{
		ComponentTexture* tex = (ComponentTexture*)gameObject->GetComponent(CompTexture);
		texture = tex->RTexture;
	}

	if (subEmitter && !subEmitterExists)
	{
		GameObject* newEmitterGO = new GameObject(this->gameObject);
		subEmitterComp = new ComponentEmitter(newEmitterGO);
		subEmitterExists = true;
	}

	if (ratio > 0.0f)
	{
		float time = timer.Read();
		if (time >= ratio)
		{
			if (App->module_time->gameState == GameState::PLAYING)
			{
				int pos = App->particle_manager->GetLastParticle();
				ActiveParticle(pos);
				particlesList.push_back(&App->particle_manager->particles[pos]);
				App->particle_manager->particles[pos].emitterpart = this;
				App->particle_manager->activeParticles++;

				timer.Start();
			}
		}
	}

	if (burstRatio > 0.0f)
	{
		float burstTime = timerBurst.Read();
		if (burstTime >= burstRatio)
		{
			if (App->module_time->gameState == GameState::PLAYING)
			{
				for (int i = 0; i < particlesBurst; ++i)
				{
					int pos = App->particle_manager->GetLastParticle();
					ActiveParticle(pos);
					particlesList.push_back(&App->particle_manager->particles[pos]);
					App->particle_manager->particles[pos].emitterpart = this;
					App->particle_manager->activeParticles++;	
				}
				timerBurst.Start();
			}
		}
	}
}

void ComponentEmitter::ActiveParticle(int pos)
{
	float3 randompoint = float3::zero;
	float3 initialpos = float3::zero;
	float3 directionvec = float3::zero;
	switch (shapeType)
	{
	case Cone_TYPE:
		randompoint = circle.RandomPointInside(App->random);
		initialpos = gameObject->transform->GetGlobalPos();
		directionvec = (randompoint - initialpos).Normalized();
		App->particle_manager->particles[pos].SetActive(gameObject->transform->GetGlobalPos(), speed, directionvec, rotation, size, life, &texture, color);
		break;
	case Sphere_TYPE:
		randompoint = sphere.RandomPointInside(App->random);
		initialpos = gameObject->transform->GetGlobalPos();
		directionvec = (randompoint - initialpos).Normalized();
		App->particle_manager->particles[pos].SetActive(randompoint, speed, directionvec, rotation, size, life, &texture, color);
		break;
	case Box_TYPE:
		randompoint = cube.RandomPointInside(App->random);
		App->particle_manager->particles[pos].SetActive(randompoint, speed, (float3::unitY * gameObject->transform->GetRotation().ToFloat3x3()).Normalized(), rotation, size, life, &texture, color);
		break;
	default:
		break;
	}
}

void ComponentEmitter::Save(JSON_Object * parent)
{
	json_object_set_number(parent, "Type", type);
	json_object_set_number(parent, "UUID", uuid);

	// Position
	//------------------------------------------------------------------------
	/*JSON_Value* pos = json_value_init_object();
	JSON_Object* positionObj = json_value_get_object(pos);

	json_object_set_value(parent, "Position", pos);

	json_object_set_number(positionObj, "X", position.x);
	json_object_set_number(positionObj, "Y", position.y);
	json_object_set_number(positionObj, "Z", position.z);*/

	// Speed
	//------------------------------------------------------------------------
	JSON_Value* sp = json_value_init_object();
	JSON_Object* speedObj = json_value_get_object(sp);

	json_object_set_value(parent, "Speed", sp);

	json_object_set_number(speedObj, "Value", speed);

	// Life
	//------------------------------------------------------------------------
	JSON_Value* lif = json_value_init_object();
	JSON_Object* lifeObj = json_value_get_object(lif);

	json_object_set_value(parent, "Life", lif);

	json_object_set_number(lifeObj, "Value", life);

	// Direction
	//------------------------------------------------------------------------
	JSON_Value* dir = json_value_init_object();
	JSON_Object* directionObj = json_value_get_object(dir);

	json_object_set_value(parent, "Direction", dir);

	json_object_set_number(directionObj, "X", direction.x);
	json_object_set_number(directionObj, "Y", direction.y);
	json_object_set_number(directionObj, "Z", direction.z);

	// Rotation
	//------------------------------------------------------------------------
	JSON_Value* rot = json_value_init_object();
	JSON_Object* roationObj = json_value_get_object(rot);

	json_object_set_value(parent, "Rotation", rot);

	json_object_set_number(roationObj, "Value", rotation);

	// Size
	//------------------------------------------------------------------------
	JSON_Value* siz = json_value_init_object();
	JSON_Object* sizeObj = json_value_get_object(siz);

	json_object_set_value(parent, "Size", siz);

	json_object_set_number(sizeObj, "Value", size);

	// Texture Path
	//------------------------------------------------------------------------
	json_object_set_string(parent, "Path", texPath.c_str());

	// Color
	//------------------------------------------------------------------------
	JSON_Value* clr = json_value_init_object();
	JSON_Object* colorObj = json_value_get_object(clr);

	json_object_set_value(parent, "Color", clr);

	json_object_set_number(colorObj, "X", color.x);
	json_object_set_number(colorObj, "Y", color.y);
	json_object_set_number(colorObj, "Z", color.z);
	json_object_set_number(colorObj, "W", color.w);

	// Ratio
	//------------------------------------------------------------------------
	JSON_Value* rat = json_value_init_object();
	JSON_Object* ratioObj = json_value_get_object(rat);

	json_object_set_value(parent, "Ratio", rat);

	json_object_set_number(ratioObj, "Value", ratio);

	// Burst Ratio
	//------------------------------------------------------------------------
	JSON_Value* burstRat = json_value_init_object();
	JSON_Object* burstRatioObj = json_value_get_object(burstRat);

	json_object_set_value(parent, "BurstRatio", burstRat);

	json_object_set_number(burstRatioObj, "Value", burstRatio);

	// Particles per burst
	//------------------------------------------------------------------------
	JSON_Value* partBurst = json_value_init_object();
	JSON_Object* particlesBurstObj = json_value_get_object(partBurst);

	json_object_set_value(parent, "ParticlesBurst", partBurst);

	json_object_set_number(particlesBurstObj, "Value", particlesBurst);

	// Shape
	//------------------------------------------------------------------------

	JSON_Value* shp = json_value_init_object();
	JSON_Object* shapeObj = json_value_get_object(shp);

	json_object_set_value(parent, "Shape", shp);

	json_object_set_number(shapeObj, "cubeX", cube.Size().x);
	json_object_set_number(shapeObj, "cubeY", cube.Size().y);
	json_object_set_number(shapeObj, "cubeZ", cube.Size().z);


	json_object_set_number(shapeObj, "SphereR", sphere.r);

	json_object_set_number(shapeObj, "CircleR", circle.r);
	json_object_set_number(shapeObj, "CircleHeight", heigh);

	json_object_set_number(shapeObj, "ShapeTYPE", shapeType);

}

void ComponentEmitter::Load(JSON_Object * parent)
{
	uuid = json_object_get_number(parent, "UUID");

	// Position
	//------------------------------------------------------------------------
	/*JSON_Object* pos = json_object_get_object(parent, "Position");
	position.x = json_object_get_number(pos, "X");
	position.y = json_object_get_number(pos, "Y");
	position.z = json_object_get_number(pos, "Z");*/

	// Speed
	//------------------------------------------------------------------------
	JSON_Object* sp = json_object_get_object(parent, "Speed");
	speed = json_object_get_number(sp, "Value");

	// Life
	//------------------------------------------------------------------------
	JSON_Object* lif = json_object_get_object(parent, "Life");
	life = json_object_get_number(lif, "Value");

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

	// Ratio
	//------------------------------------------------------------------------
	JSON_Object* ratioObj = json_object_get_object(parent, "Ratio");
	ratio = json_object_get_number(ratioObj, "Value");

	// Burst Ratio
	//------------------------------------------------------------------------
	JSON_Object* burstRatioObj = json_object_get_object(parent, "BurstRatio");
	burstRatio = json_object_get_number(burstRatioObj, "Value");

	// Particles per burst
	//------------------------------------------------------------------------
	JSON_Object* particlesBurstObj = json_object_get_object(parent, "ParticlesBurst");
	burstRatio = json_object_get_number(particlesBurstObj, "Value");

	// Shape
	//------------------------------------------------------------------------
	JSON_Object* shp = json_object_get_object(parent, "Shape");
	float3 cubesize;
	cubesize.x = json_object_get_number(shp, "cubeX");
	cubesize.y = json_object_get_number(shp, "cubeY");
	cubesize.z = json_object_get_number(shp, "cubeZ");

	cube.SetFromCenterAndSize(gameObject->transform->GetGlobalPos(), cubesize);

	sphere.r = json_object_get_number(shp, "SphereR");

	circle.r = json_object_get_number(shp, "CircleR");
	circle.pos.y = json_object_get_number(shp, "Circle Height");

	shapeType = (Shape_TYPE)(int)json_object_get_number(shp, "ShapeTYPE");
}

void ComponentEmitter::Clear()
{
	for (auto particle : particlesList)
	{
		particle->active = false;
	}
	particlesList.clear();
}