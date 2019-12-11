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

enum Billboard_AXIS {

	BillboardX,
	BillboardY,
	BillboardZ

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
	Billboard_AXIS billboardaxis = Billboard_AXIS::BillboardX;
};
