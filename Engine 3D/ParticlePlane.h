#pragma once
#include "MathGeoLib/MathGeoLib.h"

class ResourceTexture;

class ParticlePlane
{
public:
	ParticlePlane();
	~ParticlePlane();

	void Draw(float4x4 matrix, ResourceTexture* texture, float4 color);

public:
	unsigned int indexID = 0u;
	unsigned int vertexID = 0u;
	unsigned int uvID = 0u;
};