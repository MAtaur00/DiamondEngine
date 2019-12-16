#pragma once
#include "MathGeoLib/MathGeoLib.h"
#include "ResourceTexture.h"

class ComponentEmitter;



class Particle
{
public:
	Particle();
	~Particle();

	void SetActive(float3 position, float3 speed, float2 rotation, float size, float life, ResourceTexture** texture, float4 color);

	void Update(float dt);

	void CameraOrientation();

	

public:
	bool active = false;

	float life = 0.0f;
	float3 position = float3::zero;
	float3 speed = float3::zero;
	float2 rotation = float2::zero;
	float size = 0.0f;
	ResourceTexture** texture = nullptr;
	float4 color = float4::one;
	ComponentEmitter* emitterpart = nullptr;

private:
	math::Quat ownRotation = Quat::identity;
	float lifeTime = 0.0f;


};