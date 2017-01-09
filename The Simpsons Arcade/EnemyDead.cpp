#include "EnemyDead.h"

EnemyFSM::Dead::Dead()
{
}

EnemyFSM::Dead::~Dead()
{
}

State* EnemyFSM::Dead::AnimationEnd(NPC& player)
{
	// TODO: Notify scene
	return GenericFSM::Dead::AnimationEnd(player);
}
