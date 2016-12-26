#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ModuleCollision.h"

class Entity
{
public:

	Entity() : Parent(nullptr) {}

	Entity(Entity* parent) : Parent(parent) {}

	virtual ~Entity() {}

	// Entity lifecycle methods

	virtual bool Start()
	{
		return true;
	}

	virtual bool Start(bool active)
	{
		this->_active = active;
		return true;
	}

	bool Enable()
	{
		if (!_active)
			return _active = Start();
		return true;
	}

	bool Disable()
	{
		if (_active)
			return _active = !CleanUp();
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

public:
	Entity* Parent;

private:
	bool _active = true;
};

#endif // __ENTITY_H__
