#include "EnemyDamaged.h"
#include "NPC.h"

EnemyFSM::Damaged::Damaged()
{
}

EnemyFSM::Damaged::~Damaged()
{
}

void EnemyFSM::Damaged::Enter(NPC& player, const Input& input)
{
	int anim = rand() % 2;
	string animation;

	if (player.Damage == NPC::SLIGHT && player.IsAlive())
	{
		if (anim == 0)
			animation = "damaged_slight_0";
		else
			animation = "damaged_slight_1";
	}
	else
	{
		if (anim == 0)
			animation = "damaged_strong_0";
		else
			animation = "damaged_strong_1";
	}

	get_up = false;

	player.SetAnimation(animation);
}
