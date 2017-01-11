#include "HomerRevive.h"
#include "NPC.h"

HomerFSM::Revive::Revive()
{
}

HomerFSM::Revive::~Revive()
{
}

void HomerFSM::Revive::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("revive");

	_position = player.Position;
}

State* HomerFSM::Revive::HandleInput(NPC& player, const Input& input)
{
	return nullptr;
}

State* HomerFSM::Revive::Update(NPC& player, const Input& input)
{
	if (player.CurrentAnimation()->Finished())
	{
		player.Position = _position;
		player.Revive();
		return player.Idle;
	}
	
	return nullptr;
}
