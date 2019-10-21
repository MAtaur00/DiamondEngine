#include "ComponentTexture.h"



ComponentTexture::ComponentTexture(GameObject* parent) : Component(parent, CompTexture)
{
	parent->components.push_back(this);
}


ComponentTexture::~ComponentTexture()
{
}

void ComponentTexture::Inspector()
{
}
