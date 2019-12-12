#include "ComponentEmitter.h"
#include "Application.h"
#include "GameObject.h"
#include "ModuleParticleManager.h"
#include "Particle.h"
#include "ModuleTime.h"

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
				int pos = App->particle_manager->GetLastParticle();
				App->particle_manager->particles[pos].SetActive(position, speed, rotation, size, life, &texture, color);
				particlesList.push_back(&App->particle_manager->particles[pos]);
			}
		}
	}
}

void ComponentEmitter::Save(JSON_Object * parent)
{
}

void ComponentEmitter::Load(JSON_Object * parent)
{
}