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

	if (enemy->Target)
	{
		iPoint3 targetPos = enemy->Target->Position;

		iPoint3::Side side = player.Position.SidePlaced(targetPos);

		player.SetDirection(side & iPoint3::LEFT ? -1 : 1);

		int filtered = side & _last_side;

		if (filtered & iPoint3::UP)
			player.SetAnimation("walk_up");
		else if (filtered & iPoint3::DOWN)
			player.SetAnimation("walk_down");
		else if (filtered & (iPoint3::UP | iPoint3::DOWN)) // TOOD: Fix this state!
			player.SetAnimation("walk");

		_last_side = iPoint3::Side(~side);
	}

	return nullptr;
}
