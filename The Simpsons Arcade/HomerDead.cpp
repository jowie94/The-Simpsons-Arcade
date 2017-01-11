#include "HomerDead.h"
#include "NPC.h"

HomerFSM::Dead::Dead()
{
}

HomerFSM::Dead::~Dead()
{
}

State* HomerFSM::Dead::AnimationEnd(NPC& player)
{
	player.Die();
	return nullptr;
}
