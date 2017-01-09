#include "GenericDamaged.h"
#include "NPC.h"

GenericFSM::Damaged::Damaged()
{
}

GenericFSM::Damaged::~Damaged()
{
}

void GenericFSM::Damaged::Enter(NPC& player, const Input& input)
{
	int anim = rand() % 2;
	string animation;

	if (player.Damage == NPC::SLIGHT && player.IsAlive())
	{
		if (anim == 0)
			animation = "damaged_slight_0";
		else
			animation = "damaged_slight_1";
	}
	else
	{
		if (anim == 0)
			animation = "damaged_strong_0";
		else
			animation = "damaged_strong_1";
	}

	get_up = false;

	player.SetAnimation(animation);
}

State* GenericFSM::Damaged::HandleInput(NPC& player, const Input& input)
{
	return nullptr;
}

State* GenericFSM::Damaged::Update(NPC& player, const Input& input)
{
	if (player.CurrentAnimation()->Finished())
	{
		if (player.IsAlive())
		{
			if (player.Damage == NPC::STRONG && !get_up)
			{
				get_up = true;
				player.SetAnimation("get_up");
			}
			else
			{
				player.Damage = NPC::NONE;
				return player.Idle;
			}
		}
		else
		{
			return player.Dead;
		}
	}
	else if (player.Damage == NPC::STRONG && !get_up)
		player.Position.x += player.LooksRight() ? -1 : 1;

	return nullptr;
}
