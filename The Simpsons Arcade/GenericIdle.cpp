#include "GenericIdle.h"
#include "NPC.h"

GenericFSM::Idle::Idle()
{
}

GenericFSM::Idle::~Idle()
{
}

void GenericFSM::Idle::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("idle");
}

State* GenericFSM::Idle::HandleInput(NPC& player, const Input& input)
{
	int x = input.x;
	int y = input.y;

	if (input.attack == KEY_DOWN)
		return player.Attack;
	if (input.jump == KEY_DOWN)
		return player.Jump;

	if (x != 0 || y != 0)
		return player.Walking;

	return nullptr;
}

State* GenericFSM::Idle::Update(NPC& player, const Input& input)
{
	return nullptr;
}
