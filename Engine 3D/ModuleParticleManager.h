#pragma once
#include "Module.h"
#include "ComponentEmitter.h"
#include "Particle.h"
#include <list>

#define MAX_PARTICLES 10000

class ModuleParticleManager : public Module
{
public:
	ModuleParticleManager(Application* app, bool start_enabled = true);
	~ModuleParticleManager();

	int GetLastParticle();

	update_status Update();

	void Draw();

public:
	std::list<ComponentEmitter*> emitters;
	Particle particles[MAX_PARTICLES];

	int lastUsedParticle = 0;
	int activeParticles = 0;
	
};