#include "HomerDamaged.h"
#include "NPC.h"

HomerFSM::Damaged::Damaged()
{
}

HomerFSM::Damaged::~Damaged()
{
}

void HomerFSM::Damaged::Enter(NPC& player, const Input& input)
{
	int anim = rand() % 2;
	string animation;

	if (anim == 0)
		animation = "damaged_0";
	else if (anim == 1)
		animation = "damaged_1";

	player.SetAnimation(animation);
}
