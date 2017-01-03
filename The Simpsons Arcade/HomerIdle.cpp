#include "HomerIdle.h"
#include "Player.h"
#include "ModuleInput.h"
#include "Engine.h"
#include "HomerWalking.h"
#include "HomerAttack.h"

HomerFSM ::Idle::Idle()
{
}

HomerFSM::Idle::~Idle()
{
}

void HomerFSM::Idle::Enter(Player& player)
{
	player.SetAnimation("idle");
}

State* HomerFSM::Idle::HandleInput(Player& player)
{
	int x = App->input->GetAxis(0, X);
	int y = App->input->GetAxis(0, Y);

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
		return new Attack;

	if (x != 0 || y != 0)
		return new Walking;

	return nullptr;
}

State* HomerFSM::Idle::Update(Player& player)
{
	return nullptr;
}
