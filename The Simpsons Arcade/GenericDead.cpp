#include "GenericDead.h"
#include "NPC.h"

GenericFSM::Dead::Dead()
{
}

GenericFSM::Dead::~Dead()
{
}

void GenericFSM::Dead::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("dead");
}

State* GenericFSM::Dead::HandleInput(NPC& player, const Input& input)
{
	return nullptr;
}

State* GenericFSM::Dead::Update(NPC& player, const Input& input)
{
	if (player.CurrentAnimation()->Finished())
		return AnimationEnd(player);

	return nullptr;
}

State* GenericFSM::Dead::AnimationEnd(NPC& player)
{
	player.Die();
	player.Disable();
	return nullptr;
}
