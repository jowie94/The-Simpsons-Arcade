#include "HomerIdle.h"
#include "Player.h"

HomerFSM ::Idle::Idle()
{
}

HomerFSM::Idle::~Idle()
{
}

void HomerFSM::Idle::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("idle");
}

State* HomerFSM::Idle::HandleInput(NPC& player, const Input& input)
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

State* HomerFSM::Idle::Update(NPC& player, const Input& input)
{
	return nullptr;
}
