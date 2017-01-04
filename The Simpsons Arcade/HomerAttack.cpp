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

	if (pushes == 2 || x != 0)
		player.SetAnimation("attack2");
	else
		player.SetAnimation("attack1");
	pushes = (++pushes) % 3;
}

State* HomerFSM::Attack::HandleInput(Player& player)
{
	return nullptr;
}

State* HomerFSM::Attack::Update(Player& player)
{
	if (player.CurrentAnimation()->Finished())
		return player.Idle;
	
	return nullptr;
}
