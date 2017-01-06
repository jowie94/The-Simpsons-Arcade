#include "EnemyWalking.h"
#include "GenericAttack.h"
#include "NPC.h"
#include "Enemy.h"

EnemyFSM::Walking::Walking()
{
}

EnemyFSM::Walking::~Walking()
{
}

State* EnemyFSM::Walking::Update(NPC& player, const Input& input)
{
	Enemy* enemy = static_cast<Enemy*>(&player);

	return nullptr;
}
