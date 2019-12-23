#include "ModuleParticleManager.h"



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
	for (std::list<ComponentEmitter*>::iterator iterator = emitters.begin(); iterator != emitters.end(); ++iterator)
	{
		(*iterator)->Update();
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