#include "EntityFactory.h"
#include <cassert>
#include "Homer.h"
#include "Royd.h"
#include "UIEntity.h"
#include "Marge.h"
#include "Bart.h"
#include "Lisa.h"

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
	case MARGE:
		ret = new Marge;
		break;
	case BART:
		ret = new Bart;
		break;
	case LISA:
		ret = new Lisa;
		break;
	case ROYD:
		ret = new Royd;
		break;
	case UI:
		ret = new UIEntity;
	default:
		LOG("Entity %i unknown", id);
		break;
	}

	return ret;
}
