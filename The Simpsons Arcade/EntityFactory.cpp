#include "EntityFactory.h"



EntityFactory::EntityFactory()
{
}


EntityFactory::~EntityFactory()
{
}

Entity* EntityFactory::GetObject(int id) const
{
	return new Entity();
}
