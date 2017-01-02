#include "HomerWalking.h"
#include "Engine.h"
#include "ModuleInput.h"
#include "HomerIdle.h"
#include "Player.h"

HomerFSM::Walking::Walking()
{
}

HomerFSM::Walking::~Walking()
{
}

void HomerFSM::Walking::Enter(Player& player)
{
	// TODO: Set walking animation
}

State* HomerFSM::Walking::HandleInput(Player& player)
{
	int x = App->input->GetAxis(0, X);
	int y = App->input->GetAxis(0, Y);

	if (x == 0 && y == 0)
		return new Idle;

	return nullptr;
}

State* HomerFSM::Walking::Update(Player& player)
{
	int x = App->input->GetAxis(0, X);
	int y = App->input->GetAxis(0, Y);

	player.Position.x += x;
	player.Position.z += y;

	return nullptr;
}