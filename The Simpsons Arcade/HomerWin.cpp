#include "HomerWin.h"
#include "NPC.h"

HomerFSM::Win::Win()
{
}

HomerFSM::Win::~Win()
{
}

void HomerFSM::Win::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("win");
}

State* HomerFSM::Win::HandleInput(NPC& player, const Input& input)
{
	return nullptr;
}

State* HomerFSM::Win::Update(NPC& player, const Input& input)
{
	return nullptr;
}
