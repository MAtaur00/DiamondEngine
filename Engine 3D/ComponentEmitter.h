#pragma once
#include "Component.h"
#include "Timer.h"
#include "MathGeoLib/MathGeoLib.h"
#include <list>


enum Shape_TYPE {

	Cone_TYPE = -1,
	Sphere_TYPE,
	Box_TYPE

};

class Particle;
class ResourceTexture;

class ComponentEmitter : public Component
{
public:
	ComponentEmitter(GameObject* parent);
	~ComponentEmitter();

	bool Start();

	void Inspector();

	void Update();

	void ActiveParticle(int pos);

	void Save(JSON_Object* parent);

	void Load(JSON_Object* parent);

	void Clear();

public:
	Timer timer;
	Timer timerBurst;

	bool subEmitter = false;
	bool subEmitterExists = false;

	ComponentEmitter* subEmitterComp = nullptr;

	float ratio = 0.f;
	float burstRatio = 0.f;

	int particlesBurst = 0;

	float life = 0.0f;
	float speed = 1.0f;
	float rotation = 0.0f;
	float size = 1.0f;
	ResourceTexture* texture = nullptr;
	float4 color = float4::one;
	std::string texPath;
	float3 direction = float3::unitY;

	bool isSubemitter = false;

	std::list<Particle*> particlesList;

	//shapes

	AABB cube = AABB(float3(-1, -1, -1), float3(1, 1, 1));
	float3 boxSize = float3(2, 2, 2);

	Sphere sphere = Sphere(float3(0, 0, 0), 1);
	Circle circle = Circle(float3(0,0,0), float3::unitY, 1);
	float rad = 0.0f;
	float heigh = 0.0f;

	bool active = true;

	Shape_TYPE shapeType = Shape_TYPE::Cone_TYPE;
};