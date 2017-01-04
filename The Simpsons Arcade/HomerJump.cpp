#include "HomerJump.h"
#include "Player.h"
#include "Engine.h"
#include "ModuleInput.h"

HomerFSM::Jump::Jump() : ascending(true), speed(4.f)
{
}


HomerFSM::Jump::~Jump()
{
}

void HomerFSM::Jump::Enter(Player& player)
{
	player.SetAnimation("jump_up");
	ascending = true;
	speed = 4.f;
}

State* HomerFSM::Jump::HandleInput(Player& player)
{
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
		return player.Attack;
	return nullptr;
}

State* HomerFSM::Jump::Update(Player& player)
{
	if (ascending)
	{
		ascending = ascending && player.Position.y < 110 && App->input->GetKey(SDL_SCANCODE_X);

		if (!ascending)
		{
			player.SetAnimation("falling");
			speed = 0.f;
		}
	}
	else
		speed -= 0.1f;

	player.Position.y += int(speed);

	Walking::Update(player);

	if (player.Position.y <= 0)
	{
		player.Position.y = 0;
		return player.Idle;
	}

	return nullptr;
}
