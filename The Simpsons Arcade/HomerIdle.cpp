#include "HomerIdle.h"
#include "Player.h"

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
	return nullptr;
}

State* HomerFSM::Idle::Update(Player& player)
{
	return nullptr;
}
