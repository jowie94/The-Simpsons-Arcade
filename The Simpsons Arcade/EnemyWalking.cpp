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

		if (side >> 2 != _last_side >> 2) {
			float frame = player.CurrentAnimation()->GetCurrentFrameNumber();
			if ((side & iPoint3::SAME_Z) == iPoint3::SAME_Z)
				player.SetAnimation("walk");
			else if (side & iPoint3::UP)
				player.SetAnimation("walk_up");
			else if (side & iPoint3::DOWN)
				player.SetAnimation("walk_down");
			player.CurrentAnimation()->SetFrame(frame);
		}

		_last_side = side;
	}

	return nullptr;
}
