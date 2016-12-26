#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ModuleCollision.h"

class Entity
{
public:

	Entity() : parent(nullptr) {}

	Entity(Entity* parent) : parent(parent) {}

	virtual ~Entity() {}

	// Entity lifecycle methods

	virtual bool Start()
	{
		return true;
	}

	virtual bool Start(bool active)
	{
		this->active = active;
		return true;
	}

	bool Enable()
	{
		if (!active)
			return active = Start();
		return true;
	}

	bool Disable()
	{
		if (active)
			return active = !CleanUp();
		return false;
	}

	virtual void PreUpdate() {}

	virtual void Update() {}

	virtual void PostUpdate() {}

	virtual bool CleanUp()
	{
		return true;
	}

	// Callbacks
	virtual bool OnCollision(Collider origin, Collider other)
	{
		return true;
	}

private:
	bool active = true;
	Entity* parent;
};

#endif // __ENTITY_H__
