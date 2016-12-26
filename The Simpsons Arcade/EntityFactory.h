#pragma once
#include "BaseFactory.h"
#include "Entity.h"

class EntityFactory :
	public BaseFactory<Entity>
{
public:
	EntityFactory();
	~EntityFactory();


	Entity* GetObject(int id) const override;
};

