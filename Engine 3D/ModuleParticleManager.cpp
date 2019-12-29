#include "ModuleParticleManager.h"
#include "Application.h"
#include "ModuleTime.h"



ModuleParticleManager::ModuleParticleManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}


ModuleParticleManager::~ModuleParticleManager()
{
}

bool ModuleParticleManager::Start()
{
	plane = new ParticlePlane();

	return true;
}

int ModuleParticleManager::GetLastParticle()
{
	for (int i = lastUsedParticle; i < MAX_PARTICLES; i++) {
		if (!particles[i].active) {
			lastUsedParticle = i;
			return i;
		}
	}

	for (int i = 0; i < lastUsedParticle; i++) {
		if (!particles[i].active) {
			lastUsedParticle = i;
			return i;
		}
	}
	return 0;
}

update_status ModuleParticleManager::Update()
{
	if (!ImGui::IsAnyWindowFocused)
	{
		if (Time::gameState == GameState::PLAYING)
		{
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			{
				if (firework)
					firework->Start();
			}
		}
	}

	for (std::list<ComponentEmitter*>::iterator iterator = emitters.begin(); iterator != emitters.end(); ++iterator)
	{
		(*iterator)->Update();
	}

	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		if (particles[i].active)
		{
			particles[i].Update(App->module_time->dt);
		}
	}
	Draw();

	return UPDATE_CONTINUE;
}

void ModuleParticleManager::Draw()
{
	for (int i = 0; i < MAX_PARTICLES; ++i)
	{
		if (particles[i].active)
		{
			particles[i].Draw();
		}
	}
}

void ModuleParticleManager::StartEmitters()
{
	for (std::list<ComponentEmitter*>::iterator iterator = emitters.begin(); iterator != emitters.end(); ++iterator)
	{
		if ((*iterator) != firework)
			(*iterator)->Start();
	}
}

void ModuleParticleManager::ClearEmitters()
{
	for (std::list<ComponentEmitter*>::iterator iterator = emitters.begin(); iterator != emitters.end(); ++iterator)
	{
		(*iterator)->Clear();
	}
}