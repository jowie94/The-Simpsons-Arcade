#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "NPC.h"

class Enemy :
	public NPC
{
public:
	Enemy();
	virtual ~Enemy();

	void Update() override;

	void BeginAttack() override;
	Entity* Target = nullptr;
protected:
	int damage = 1;
};

#endif // __ENEMY_H__
