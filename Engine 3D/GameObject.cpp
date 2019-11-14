#include "GameObject.h"
#include "Application.h"
#include "pcg/pcg_basic.h"
using namespace std;


GameObject::GameObject(GameObject* parent, const char* name, bool addToList)
{
	this->parent = parent;
	if (parent)
		parent->childs.push_back(this);
	if (name)
		this->name = name;

	if (addToList)
		App->game_object->gameObjects.push_back(this);

	transform = new ComponentTransform(this);

	uuid = pcg32_random();

	originalBoundingBox.SetNegativeInfinity();
	boundingBox.SetNegativeInfinity();
}


GameObject::~GameObject()
{
	App->game_object->gameObjects.remove(this);
}

bool GameObject::HasComponent(Object_Type type)
{
	if (type == CompTransform && transform)
	{
		return true;
	}
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
	if (type == CompTransform && transform)
	{
		return transform;
	}
	for (list<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->type == type)
		{
			return (*it);
		}
	}
	return nullptr;
}

void GameObject::Save(JSON_Object * parent)
{
	json_object_set_string(parent, "Name", name.data());
	json_object_set_number(parent, "UUID", uuid);
	json_object_set_boolean(parent, "Active", active);

	if (this->parent)
	{
		json_object_set_number(parent, "UUID", this->parent->uuid);
	}

	JSON_Value* componentsValue = json_value_init_array();
	JSON_Array* componentsObj = json_value_get_array(componentsValue);

	json_object_set_value(parent, "Components", componentsValue);

	for (auto child : childs)
	{
		JSON_Value* childValue = json_value_init_object();
		JSON_Object* childObj = json_value_get_object(childValue);

		child->Save(childObj);

		json_array_append_value(componentsObj, childValue);
	}
}