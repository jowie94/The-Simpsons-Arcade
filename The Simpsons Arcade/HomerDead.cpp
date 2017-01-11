#include "HomerDead.h"
#include "NPC.h"
#include "Player.h"
#include "ModuleAudio.h"

HomerFSM::Dead::Dead()
{
}

HomerFSM::Dead::~Dead()
{
}

void HomerFSM::Dead::Enter(NPC& player, const Input& input)
{
	Player* pl = static_cast<Player*>(&player);

	if (pl->FxDizzy != -1 && pl->Lifes > 0)
		App->audio->PlayFx(pl->FxDizzy);

	GenericFSM::Dead::Enter(player, input);
}

State* HomerFSM::Dead::AnimationEnd(NPC& player)
{
	player.Die();
	return nullptr;
}
