#include "HomerWalking.h"
#include "Player.h"

HomerFSM::Walking::Walking()
{
}

HomerFSM::Walking::~Walking()
{
}

void HomerFSM::Walking::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("walk");
}

State* HomerFSM::Walking::HandleInput(NPC& player, const Input& input)
{
	int x = input.x;
	int y = input.y;

	if (input.attack)
		return player.Attack;
	if (input.jump)
		return player.Jump;

	if (x == 0 && y == 0)
		return player.Idle;

	if (!up && y > 0)
		player.SetAnimation("walk_up");
	else if (up && y <= 0)
		player.SetAnimation("walk");

	up = y > 0;

	return nullptr;
}

State* HomerFSM::Walking::Update(NPC& player, const Input& input)
{
	int x = input.x;
	int y = input.y;

	player.Position.x += x * 2;
	player.Position.z += y * 2;

	player.SetDirection(x);

	return nullptr;
}
