#include "GenericAttack.h"
#include "NPC.h"

GenericFSM::Attack::Attack()
{
}

GenericFSM::Attack::~Attack()
{
}

void GenericFSM::Attack::Enter(NPC& player, const Input& input)
{
	int x = input.x;

	string attack;

	if (pushes == 2 || x != 0)
	{
		if (player.Position.y > 0)
			attack = "air_attack1";
		else
			attack = "attack2";
	}
	else
	{
		if (player.Position.y > 0)
			attack = "air_attack2";
		else
			attack = "attack1";
	}

	player.BeginAttack();
	player.SetAnimation(attack);

	pushes = (++pushes) % 3;
}

State* GenericFSM::Attack::HandleInput(NPC& player, const Input& input)
{
	return nullptr;
}

State* GenericFSM::Attack::Update(NPC& player, const Input& input)
{
	if (player.Position.y != 0)
	{
		player.Position.y -= 6;
		player.Position.x += 8 * (player.LooksRight() ? 1 : -1);
	}

	if (player.Position.y < 0 || player.CurrentAnimation()->Finished() && player.Position.y == 0)
	{
		player.Position.y = 0;
		player.FinishAttack();
		return player.Idle;
	}

	return nullptr;
}
