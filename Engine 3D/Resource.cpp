#include "Resource.h"


Resource::~Resource()
{
}

bool Resource::operator==(Resource other)
{
	if (this->type == other.type)
	{
		if (strcmp(this->name.data(), other.name.data()) == 0)
			return true;
	}
	return false;
}
