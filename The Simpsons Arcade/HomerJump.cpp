#include "HomerJump.h"
#include "Player.h"

HomerFSM::Jump::Jump() : ascending(true), speed(4.f)
{
}


HomerFSM::Jump::~Jump()
{
}

void HomerFSM::Jump::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("jump_up");
	ascending = true;
	speed = 4.f;
}

State* HomerFSM::Jump::HandleInput(NPC& player, const Input& input)
{
	if (input.attack)
		return player.Attack;
	return nullptr;
}

State* HomerFSM::Jump::Update(NPC& player, const Input& input)
{
	if (ascending)
	{
		ascending = ascending && player.Position.y < 110 && input.jump;

		if (!ascending)
		{
			player.SetAnimation("falling");
			speed = 0.f;
		}
	}
	else
		speed -= 0.1f;

	player.Position.y += int(speed);

	Walking::Update(player, input);

	if (player.Position.y <= 0)
	{
		player.Position.y = 0;
		return player.Idle;
	}

	return nullptr;
}
