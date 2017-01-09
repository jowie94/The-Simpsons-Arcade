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
		Target = *next(players.begin(), player);
	}

	NPC::Update();
}

void Enemy::BeginAttack()
{
	NPC::BeginAttack();

	attack_collider->type = ENEMY_ATTACK;
}
