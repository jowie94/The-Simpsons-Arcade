#include "HomerWalking.h"
#include "Player.h"

HomerFSM::Walking::Walking()
{
}

HomerFSM::Walking::~Walking()
{
}

State* HomerFSM::Walking::HandleInput(NPC& player, const Input& input)
{
	int x = input.x;
	int y = input.y;

	State* next = GenericFSM::Walking::HandleInput(player, input);

	if (next)
		return next;

	if (!up && y > 0)
		player.SetAnimation("walk_up");
	else if (up && y <= 0)
		player.SetAnimation("walk");

	up = y > 0;

	return nullptr;
}
