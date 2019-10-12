#include "GameObject.h"



GameObject::GameObject(GameObject* parent, const char* name)
{
	this->parent = parent;
	if (parent)
		parent->childs.push_back(this);
	if (name)
		this->name = name;

	transform = new ComponentTransform(this);

	components.push_back((Component*)transform);
}


GameObject::~GameObject()
{
}