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
	if (enemy->Target)
		return player.Walking;

	return GenericFSM::Idle::HandleInput(player, input);
}
