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

public:
	Entity* Target = nullptr;
};

#endif // __ENEMY_H__
