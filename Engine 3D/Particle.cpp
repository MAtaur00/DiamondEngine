#include "Particle.h"
#include "Globals.h"
#include "Application.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::SetActive(float3 position, float3 speed, float2 rotation, float size, float life, ResourceTexture** texture, float4 color)
{
	active = true;

	this->position = position;
	this->speed = speed;
	this->rotation = rotation * DEGTORAD;
	this->size = size;
	this->life = life;
	this->texture = texture;
	this->color = color;


}

void Particle::Update(float dt)
{
	if(life > lifeTime)
	{
		position += (speed.Mul(dt));

		CameraOrientation();

		lifeTime += dt;
	}
	else
	{
		emitterpart->particlesList.remove(this);
		App->particle_manager->activeParticles--;
	}



}

void Particle::CameraOrientation()
{

	float3 z = -App->camera->compCamera->frustum.front;
	float3 y = App->camera->compCamera->frustum.up;

	float3 x = y.Cross(z);

	ownRotation.Set(float3x3(x, y, z));

}
