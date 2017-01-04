#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ModuleCollision.h"
#include "Point3.h"

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

	bool IsEnabled()
	{
		return _active;
	}

	virtual void PreUpdate() {}

	virtual void Update() {}

	virtual void PostUpdate() {}

	virtual bool CleanUp()
	{
		return true;
	}

	// Callbacks
	virtual bool OnCollision(Collider& origin, Collider& other)
	{
		return true;
	}

public:
	Entity* Parent;
	iPoint3 Position;
	Collider* FeetCollider = nullptr;

private:
	bool _active = true;
};

#endif // __ENTITY_H__
