#include "HomerWalking.h"
#include "Engine.h"
#include "ModuleInput.h"
#include "Player.h"

HomerFSM::Walking::Walking()
{
}

HomerFSM::Walking::~Walking()
{
}

void HomerFSM::Walking::Enter(Player& player)
{
	player.SetAnimation("walk");
}

State* HomerFSM::Walking::HandleInput(Player& player)
{
	int x = App->input->GetAxis(0, X);
	int y = App->input->GetAxis(0, Y);

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
		return player.Attack;
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
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

State* HomerFSM::Walking::Update(Player& player)
{
	int x = App->input->GetAxis(0, X);
	int y = App->input->GetAxis(0, Y);

	player.Position.x += x * 2;
	player.Position.z += y * 2;

	player.SetDirection(x);

	return nullptr;
}
