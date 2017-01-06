#include "GenericWalking.h"
#include "NPC.h"


GenericFSM::Walking::Walking()
{
}

GenericFSM::Walking::~Walking()
{	
}

void GenericFSM::Walking::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("walk");
}

State* GenericFSM::Walking::HandleInput(NPC& player, const Input& input)
{
	if (input.attack == KEY_DOWN)
		return player.Attack;
	if (input.jump == KEY_DOWN)
		return player.Jump;

	if (input.x == 0 && input.y == 0)
		return player.Idle;

	return nullptr;
}

State* GenericFSM::Walking::Update(NPC& player, const Input& input)
{
	int x = input.x;
	int y = input.y;

	player.Position.x += x * 2;
	player.Position.z += y * 2;

	player.SetDirection(x);

	return nullptr;
}
