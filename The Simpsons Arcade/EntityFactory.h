#ifndef __ENTITYFACTORY_H__
#define __ENTITYFACTORY_H__

#include "BaseFactory.h"
#include "Entity.h"

class EntityFactory :
	public BaseFactory<Entity>
{
public:
	enum Entities
	{
		HOMER = 0,
		ROYD,
		MARGE,
		BART,
		LISA,
		UI,
		UNKNOWN
	};

	EntityFactory();
	~EntityFactory();

	Entity* GetObject(int id) const override;
};

#endif // __ENTITYFACTORY_H__
