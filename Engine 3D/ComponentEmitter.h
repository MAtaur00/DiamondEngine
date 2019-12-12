#pragma once
#include "Component.h"
#include "Timer.h"
#include "MathGeoLib/MathGeoLib.h"
#include <list>

class ComponentEmitter : public Component
{
public:
	ComponentEmitter(GameObject* parent);
	~ComponentEmitter();

	void Inspector();

	void Update();

	void Save(JSON_Object* parent);

	void Load(JSON_Object* parent);

public:
	Timer timer;

	float ratio = 0.f;

	float life = 0.0f;
	float3 position = float3::zero;
	float3 speed = float3::zero;
	float2 rotation = float2::zero;
	float size = 0.0f;
	ResourceTexture* texture = nullptr;
	float4 color = float4::one;

	std::list<Particle*> particlesList;
};