#include "Enemy.h"
#include "ModuleSceneManager.h"
#include "Scene.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	if (!Target)
	{
		list<Entity*> players;
		App->scene_manager->CurrentScene()->PlayerList(players);
		int player = rand() % players.size();
		NPC* target = static_cast<NPC*>(*next(players.begin(), player));
		if (target->IsAlive())
			Target = target;
	}

	NPC* target = static_cast<NPC*>(Target);

	if (target && !target->IsAlive())
	{
		if (attack_collider)
			FinishAttack();
		Target = nullptr;
		SwitchState(Idle);
	}

	NPC::Update();
}

void Enemy::BeginAttack()
{
	NPC::BeginAttack();

	attack_collider->type = ENEMY_ATTACK;
}

void Enemy::Die()
{
	NPC::Die();
	App->scene_manager->CurrentScene()->EnemyDefeated();
}
