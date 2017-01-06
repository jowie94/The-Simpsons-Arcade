#include "EntityFactory.h"
#include <cassert>
#include "Homer.h"
#include "Royd.h"

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
	case ROYD:
		ret = new Royd;
		break;
	default:
		LOG("Entity %i unknown", id);
		break;
	}

	return ret;
}
