#include "Particle.h"
#include "Globals.h"
#include "Application.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::SetActive(float3 position, float speed, float3 direction, float rotation, float size, float life, ResourceTexture** texture, float4 color)
{
	active = true;

	this->position = position;
	this->speed = speed;
	this->rotation = rotation * DEGTORAD;
	this->size = size;
	this->life = life;
	this->texture = texture;
	this->color = color;
	this->direction = direction;

	plane = App->particle_manager->plane;
}

void Particle::Update(float dt)
{
	if(life > lifeTime)
	{
		position += (direction.Mul(speed * dt));

		CameraOrientation();

		lifeTime += dt;
	}
	else
	{
		emitterpart->particlesList.remove(this);
		App->particle_manager->activeParticles--;
		active = false;

		if (emitterpart->subEmitter)
		{
			if (App->module_time->gameState == GameState::PLAYING)
			{
				for (int i = 0; i < emitterpart->particlesBurst; ++i)
				{
					int pos = App->particle_manager->GetLastParticle();
					App->particle_manager->particles[pos].SetActive(position, speed, direction, rotation, size, life, &emitterpart->texture, color);
					emitterpart->particlesList.push_back(&App->particle_manager->particles[pos]);
					
					if (emitterpart->subEmitterComp)
					{
						App->particle_manager->particles[pos].emitterpart = emitterpart->subEmitterComp;
					}
					App->particle_manager->activeParticles++;
				}
			}
		}
	}
	//ownRotation = ownRotation.Mul(Quat::RotateZ(rotation));
}

void Particle::CameraOrientation()
{
	float3 z = -App->renderer3D->current_cam->frustum.front;
	float3 y = App->renderer3D->current_cam->frustum.up;
	float3 x = y.Cross(z);

	ownRotation.Set(float3x3(x, y, z));
}

void Particle::Draw()
{
	if (plane)
	{
		plane->Draw(float4x4::FromTRS(position, ownRotation, float3(size)), *texture, color);
	}
}