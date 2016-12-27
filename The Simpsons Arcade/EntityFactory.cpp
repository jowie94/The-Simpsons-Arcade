#include "EntityFactory.h"
#include "Homer.h"
#include <cassert>


EntityFactory::EntityFactory()
{
}


EntityFactory::~EntityFactory()
{
}

Entity* EntityFactory::GetObject(int id) const
{
	assert(id < UNKNOWN);

	Entity* ret = nullptr;

	switch (id)
	{
	case HOMER:
		ret = new Homer;
		break;
	default:
		LOG("Entity %i unknown", id);
		break;
	}

	return ret;
}
