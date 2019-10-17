#include "GameObject.h"
using namespace std;


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

bool GameObject::HasComponent(Object_Type type)
{
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == type)
		{
			return true;
		}
	}
	return false;
}

Component * GameObject::GetComponent(Object_Type type)
{
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == type)
		{
			return (*it);
		}
	}
	return nullptr;
}
