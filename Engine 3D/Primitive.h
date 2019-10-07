
#pragma once
#include "glmath.h"
#include "Color.h"

enum PrimitiveTypes
{
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder,
	P_Mesh
};

class Primitive
{
public:

	Primitive();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const vec3 &u);
	void			Scale(float x, float y, float z);
	PrimitiveTypes	GetType() const;

public:
	
	Color color;
	mat4x4 transform;
	bool axis,wire;

protected:
	PrimitiveTypes type;
};

// ============================================
class PrimitiveCube : public Primitive
{
public :
	PrimitiveCube();
	PrimitiveCube(float sizeX, float sizeY, float sizeZ);
	void InnerRender() const;
public:
	vec3 size;
};

// ============================================
class PrimitiveSphere : public Primitive
{
public:
	PrimitiveSphere();
	PrimitiveSphere(float radius);
	void InnerRender() const;
public:
	float radius;
};

// ============================================
class PrimitiveCylinder : public Primitive
{
public:
	PrimitiveCylinder();
	PrimitiveCylinder(float radius, float height);
	void InnerRender() const;
public:
	float radius;
	float height;
};

// ============================================
class PrimitiveLine : public Primitive
{
public:
	PrimitiveLine();
	PrimitiveLine(float x, float y, float z);
	void InnerRender() const;
public:
	vec3 origin;
	vec3 destination;
};

// ============================================
class PrimitivePlane : public Primitive
{
public:
	PrimitivePlane();
	PrimitivePlane(float x, float y, float z, float d);
	void InnerRender() const;
public:
	vec3 normal;
	float constant;
};

// ============================================

template <typename T>
struct buffer 
{
	uint id = 0u;
	uint size = 0u;
	T* data = nullptr;
};

class Mesh : public Primitive
{
public:
	Mesh();
	void InnerRender() const;
public:
	int id = -1;
	buffer<uint> index;
	buffer<float> vertex;
};