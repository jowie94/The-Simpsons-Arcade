#include "GenericDamaged.h"
#include "NPC.h"

GenericFSM::Damaged::Damaged()
{
}

GenericFSM::Damaged::~Damaged()
{
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
