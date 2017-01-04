#include "HomerAttack.h"
#include "Player.h"
#include "Engine.h"
#include "ModuleInput.h"

HomerFSM::Attack::Attack()
{
}


HomerFSM::Attack::~Attack()
{
}

void HomerFSM::Attack::Enter(Player& player)
{
	int x = App->input->GetAxis(0, X);

	string attack;

	if (pushes == 2 || x != 0)
	{
		if (player.Position.y > 0)
			attack = "air_attack1";
		else
			attack = "attack2";
	}
	else
	{
		if (player.Position.y > 0)
			attack = "air_attack2";
		else
			attack = "attack1";
	}

	player.SetAnimation(attack);

	pushes = (++pushes) % 3;
}

State* HomerFSM::Attack::HandleInput(Player& player)
{
	return nullptr;
}

State* HomerFSM::Attack::Update(Player& player)
{
	if (player.Position.y != 0)
	{
		player.Position.y -= 6;
		player.Position.x += 8 * (player.LooksRight() ? 1 : -1);
	}

	if (player.Position.y < 0 || player.CurrentAnimation()->Finished() && player.Position.y == 0)
	{
		player.Position.y = 0;
		return player.Idle;
	}
	
	return nullptr;
}
