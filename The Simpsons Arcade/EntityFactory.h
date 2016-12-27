#pragma once
#include "BaseFactory.h"
#include "Entity.h"

class EntityFactory :
	public BaseFactory<Entity>
{
public:
	enum Entities
	{
		HOMER = 0,
		UNKNOWN
	};

	EntityFactory();
	~EntityFactory();

	Entity* GetObject(int id) const override;
};

