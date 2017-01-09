#include "EnemyIdle.h"
#include "NPC.h"
#include "Enemy.h"

EnemyFSM::Idle::Idle()
{
}

EnemyFSM::Idle::~Idle()
{
}

State* EnemyFSM::Idle::HandleInput(NPC& player, const Input& input)
{
	Enemy* enemy = static_cast<Enemy*>(&player);
	NPC* target = static_cast<NPC*>(enemy->Target);
	if (enemy->Target && target->IsAlive())
		return player.Walking;

	return GenericFSM::Idle::HandleInput(player, input);
}
