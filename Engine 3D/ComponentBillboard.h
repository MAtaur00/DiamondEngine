#pragma once

#include "Component.h"
#include "GameObject.h"


enum Billboard_TYPE
{
	BillboardNone = -1,

	BillboardScreen,
	BillboardWorld,
	BillboardAxially

};

class ComponentBillboard :
	public Component
{
public:
	ComponentBillboard(GameObject* parent);
	~ComponentBillboard();

	void Inspector();

	void Update();


public:

	Billboard_TYPE billboardtype = Billboard_TYPE::BillboardNone;
};
