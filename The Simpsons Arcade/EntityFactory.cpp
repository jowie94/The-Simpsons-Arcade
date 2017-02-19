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
	NPC* player = nullptr;

	switch (id)
	{
	case MARGE:
		player = new Player;
		player->LoadFromJson("Simpsons/marge.json");
		break;
	case HOMER:
		player = new Player;
		player->LoadFromJson("Simpsons/homer.json");
		break;
	case BART:
		player = new Player;
		player->LoadFromJson("Simpsons/bart.json");
		break;
	case LISA:
		player = new Player;
		player->LoadFromJson("Simpsons/lisa.json");
		break;
	case ROYD:
		ret = new Royd;
		break;
	case UI:
		ret = new UIEntity;
		break;
	default:
		LOG("Entity %i unknown", id);
		break;
	}

	return player ? player : ret;
}
