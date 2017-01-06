#include "HomerIdle.h"
#include "Player.h"
#include "ModuleInput.h"
#include "Engine.h"

HomerFSM ::Idle::Idle()
{
}

HomerFSM::Idle::~Idle()
{
}

void HomerFSM::Idle::Enter(NPC& player)
{
	player.SetAnimation("idle");
}

State* HomerFSM::Idle::HandleInput(NPC& player)
{
	int x = App->input->GetAxis(0, X);
	int y = App->input->GetAxis(0, Y);

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
		return player.Attack;
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		return player.Jump;

	if (x != 0 || y != 0)
		return player.Walking;

	return nullptr;
}

State* HomerFSM::Idle::Update(NPC& player)
{
	return nullptr;
}
