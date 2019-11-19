#pragma once
#include "Component.h"
#include "MathGeoLib/MathGeoLib.h"

class ComponentCamera :
	public Component
{
public:
	ComponentCamera(GameObject* parent);
	~ComponentCamera();

	void Inspector();

	float4x4 GetViewMatrix();
	float4x4 GetProjectionMatrix();

	void Save(JSON_Object* parent);

	void Load(JSON_Object* parent);

public:

	Frustum frustum;
};