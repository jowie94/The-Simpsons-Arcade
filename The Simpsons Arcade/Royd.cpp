#include "Royd.h"
#include "ModuleTextures.h"
#include "EnemyIdle.h"
#include "EnemyWalking.h"
#include "EnemyDamaged.h"
#include "EnemyDead.h"
#include "EnemyAttack.h"

Royd::Royd()
{
}

Royd::~Royd()
{
}

bool Royd::Start()
{
	SDL_Color key = { 89, 253, 66, 0 };
	graphics = App->textures->Load("Simpsons/royd.png", &key);
	center = 12; // Royd's center
	life = 2;

	SpriteAnimation idle;
	idle.frames.push_back({ { 16, 256, 33, 64 }, iPoint(4, 64) });

	AddAnimation("idle", idle);

	SpriteAnimation walk;
	walk.frames.push_back({ { 16, 16, 20, 64 }, iPoint(0, 64) });
	walk.frames.push_back({ { 64, 16, 25, 64 }, iPoint(4, 64) });
	walk.frames.push_back({ { 112, 17, 32, 63 }, iPoint(6, 63) });
	walk.frames.push_back({ { 160, 17, 24, 63 }, iPoint(3, 63) });
	walk.frames.push_back({ { 208, 17, 23, 63 }, iPoint(0, 63) });
	walk.frames.push_back({ { 256, 17, 27, 63 }, iPoint(3, 63) });
	walk.frames.push_back({ { 304, 18, 32, 62 }, iPoint(8, 62) });
	walk.frames.push_back({ { 352, 16, 24, 64 }, iPoint(3, 64) });
	walk.speed = 0.2f;

	AddAnimation("walk", walk);

	SpriteAnimation walk_up;
	walk_up.frames.push_back({ { 16, 98, 25, 62 }, iPoint(0, 62) });
	walk_up.frames.push_back({ { 64, 98, 27, 62 }, iPoint(0, 62) });
	walk_up.frames.push_back({ { 112, 98, 32, 62 }, iPoint(1, 62) });
	walk_up.frames.push_back({ { 160, 100, 27, 60 }, iPoint(0, 60) });
	walk_up.frames.push_back({ { 208, 99, 26, 61 }, iPoint(0, 61) });
	walk_up.frames.push_back({ { 256, 98, 28, 62 }, iPoint(2, 62) });
	walk_up.frames.push_back({ { 304, 99, 31, 61 }, iPoint(5, 61) });
	walk_up.frames.push_back({ { 352, 100, 25, 60 }, iPoint(0, 60) });
	walk_up.speed = 0.2f;

	AddAnimation("walk_up", walk_up);

	SpriteAnimation walk_down;
	walk_down.frames.push_back({ { 16, 176, 29, 64 }, iPoint(8, 64) });
	walk_down.frames.push_back({ { 64, 177, 25, 63 }, iPoint(4, 63) });
	walk_down.frames.push_back({ { 112, 178, 23, 62 }, iPoint(2, 61) });
	walk_down.frames.push_back({ { 160, 177, 24, 63 }, iPoint(3, 63) });
	walk_down.frames.push_back({ { 208, 176, 23, 64 }, iPoint(2, 64) });
	walk_down.frames.push_back({ { 256, 177, 25, 63 }, iPoint(6, 63) });
	walk_down.frames.push_back({ { 304, 178, 30, 62 }, iPoint(7, 62) });
	walk_down.frames.push_back({ { 352, 177, 39, 63 }, iPoint(11, 63) });
	walk_down.speed = 0.2f;

	AddAnimation("walk_down", walk_down);

	SpriteAnimation attack1;
	attack1.frames.push_back({ { 112, 338, 28, 62 }, iPoint(1, 62) });
	attack1.frames.push_back({ { 160, 340, 32, 60 }, iPoint(4, 60) });
	attack1.frames.push_back({ { 208, 340, 39, 60 }, iPoint(2, 60) });
	attack1.frames.push_back({ { 256, 344, 50, 56 }, iPoint(8, 56) });
	attack1.frames.push_back({ { 320, 340, 39, 60 }, iPoint(2, 60) });
	attack1.loop = false;
	attack1.speed = 0.2f;

	AddAnimation("attack1", attack1);

	SpriteAnimation attack2;
	attack2.frames.push_back({ { 384, 338, 56, 62 }, iPoint(15, 62) });
	attack2.frames.push_back({ { 448, 338, 39, 62 }, iPoint(6, 62) });
	attack2.frames.push_back({ { 496, 341, 43, 59 }, iPoint(6, 59) });
	attack2.frames.push_back({ { 544, 338, 43, 62 }, iPoint(6, 62) });
	attack2.loop = false;
	attack2.speed = 0.2f;

	AddAnimation("attack2", attack2);

	SpriteAnimation damaged_slight_0;
	damaged_slight_0.frames.push_back({ { 16, 562, 29, 62 }, iPoint(0, 62) });
	damaged_slight_0.frames.push_back({ { 64, 561, 29, 63 }, iPoint(9, 63) });
	damaged_slight_0.frames.push_back({ { 112, 565, 32, 59 }, iPoint(16, 59) });
	damaged_slight_0.frames.push_back({ { 160, 561, 27, 63 }, iPoint(9, 63) });
	damaged_slight_0.frames.push_back({ { 208, 562, 26, 62 }, iPoint(0, 62) });
	damaged_slight_0.speed = 0.2f;

	AddAnimation("damaged_slight_0", damaged_slight_0);

	SpriteAnimation damaged_slight_1;
	damaged_slight_1.frames.push_back({ { 16, 644, 32, 60 }, iPoint(3, 60) });
	damaged_slight_1.frames.push_back({ { 64, 646, 35, 58 }, iPoint(2, 58) });
	damaged_slight_1.frames.push_back({ { 112, 654, 40, 50 }, iPoint(0, 50) });
	damaged_slight_1.frames.push_back({ { 160, 643, 30, 61 }, iPoint(1, 61) });
	damaged_slight_1.speed = 0.2f;

	AddAnimation("damaged_slight_1", damaged_slight_1);

	SpriteAnimation damaged_strong_0;
	damaged_strong_0.frames.push_back({ { 16, 480, 37, 64 }, iPoint(10, 64) });
	damaged_strong_0.frames.push_back({ { 64, 484, 38, 60 }, iPoint(1, 60) });
	damaged_strong_0.frames.push_back({ { 112, 485, 40, 59 }, iPoint(0, 59) });
	damaged_strong_0.frames.push_back({ { 160, 484, 40, 60 }, iPoint(0, 60) });
	damaged_strong_0.frames.push_back({ { 208, 484, 40, 60 }, iPoint(0, 60) });
	damaged_strong_0.frames.push_back({ { 256, 484, 36, 60 }, iPoint(0, 60) });
	damaged_strong_0.frames.push_back({ { 304, 489, 47, 55 }, iPoint(9, 60) });
	damaged_strong_0.frames.push_back({ { 256, 424, 60, 40 }, iPoint(34, 40) });
	damaged_strong_0.frames.push_back({ { 336, 420, 61, 44 }, iPoint(42, 37) });
	damaged_strong_0.speed = 0.2f;

	AddAnimation("damaged_strong_0", damaged_strong_0);

	SpriteAnimation damaged_strong_1;
	damaged_strong_1.frames.push_back({ { 16, 418, 40, 46 }, iPoint(5, 46) });
	damaged_strong_1.frames.push_back({ { 64, 424, 46, 40 }, iPoint(20, 40) });
	damaged_strong_1.frames.push_back({ { 112, 418, 40, 46 }, iPoint(5, 46) });
	damaged_strong_1.frames.push_back({ { 160, 424, 46, 40 }, iPoint(5, 40) });
	damaged_strong_1.frames.push_back({ { 208, 418, 40, 46 }, iPoint(5, 46) });
	damaged_strong_1.frames.push_back({ { 256, 424, 60, 40 }, iPoint(34, 40) });
	damaged_strong_1.frames.push_back({ { 336, 420, 61, 44 }, iPoint(42, 37) });
	damaged_strong_1.speed = 0.2f;

	AddAnimation("damaged_strong_1", damaged_strong_1);

	SpriteAnimation get_up;
	get_up.frames.push_back({ { 16, 730, 56, 54 }, iPoint(24, 44) });
	get_up.frames.push_back({ { 80, 730, 56, 54 }, iPoint(24, 44) });
	get_up.frames.push_back({ { 144, 730, 56, 54 }, iPoint(24, 44) });
	get_up.frames.push_back({ { 208, 730, 56, 54 }, iPoint(24, 44) });
	get_up.frames.push_back({ { 272, 739, 55, 45 }, iPoint(10, 45) });
	get_up.frames.push_back({ { 336, 740, 54, 44 }, iPoint(10, 45) });
	get_up.frames.push_back({ { 400, 739, 55, 45 }, iPoint(10, 45) });
	get_up.frames.push_back({ { 464, 740, 54, 44 }, iPoint(10, 45) });
	get_up.frames.push_back({ { 528, 727, 50, 57 }, iPoint(1, 57) });
	get_up.frames.push_back({ { 592, 727, 49, 57 }, iPoint(1, 57) });
	get_up.frames.push_back({ { 656, 727, 50, 57 }, iPoint(1, 57) });
	get_up.speed = 0.1f;

	AddAnimation("get_up", get_up);

	SpriteAnimation dead;
	dead.frames.push_back({ { 416, 416, 67, 48 }, iPoint(42, 41) });
	dead.frames.push_back({ { 416, 416, 0, 0 }, iPoint(42, 41) });
	dead.frames.push_back({ { 416, 416, 67, 48 }, iPoint(42, 41) });
	dead.frames.push_back({ { 416, 416, 0, 0 }, iPoint(42, 41) });
	dead.frames.push_back({ { 496, 413, 67, 51 }, iPoint(42, 44) });
	dead.frames.push_back({ { 496, 413, 0, 0 }, iPoint(42, 44) });
	dead.frames.push_back({ { 496, 413, 67, 51 }, iPoint(42, 44) });
	dead.frames.push_back({ { 496, 413, 0, 0 }, iPoint(42, 44) });
	dead.frames.push_back({ { 576, 435, 67, 29 }, iPoint(42, 22) });
	dead.frames.push_back({ { 576, 435, 0, 0 }, iPoint(42, 44) });
	dead.frames.push_back({ { 576, 435, 67, 29 }, iPoint(42, 22) });
	dead.frames.push_back({ { 576, 435, 0, 0 }, iPoint(42, 44) });
	dead.loop = false;
	dead.speed = 0.1f;

	AddAnimation("dead", dead);

	Idle = new EnemyFSM::Idle;
	Walking = new EnemyFSM::Walking;
	Attack = new EnemyFSM::Attack;
	Damaged = new EnemyFSM::Damaged;
	Dead = new EnemyFSM::Dead;

	SwitchState(Idle);

	FeetCollider = App->collision->AddCollider(iRectangle3(0, 0, 0, 20, 10), this);
	FeetCollider->type = ENEMY;

	return graphics != nullptr;
}

void Royd::PreUpdate()
{
	if (Target)
	{
		iPoint3 vec = Target->Position - Position;
		fPoint3 direction(float(vec.x), float(vec.y), float(vec.z));
		float distance = float(direction.Magnitude());
		direction = direction / distance;
		if (abs(vec.x) > 40 || !_touching_player)
			_prepared_input.x = int(direction.x < 0 ? floor(direction.x) : ceil(direction.x));
		if (abs(vec.z) > 5)
			_prepared_input.y = int(direction.z < 0 ? floor(direction.z) : ceil(direction.z));

		if (_touching_player && !_attacking)
		{
			_prepared_input.attack = KEY_DOWN;
			_touching_player = false;
			_attacking = true;
		}
		else if (_attacking )
		{
			if (abs(vec.x) < 60)
				_prepared_input.x = int((direction.x < 0 ? floor(direction.x) : ceil(direction.x)) * -1);
			else
			{
				_touching_player = false;
				_attacking = false;
			}
		}
	}

	Enemy::PreUpdate();
}

void Royd::PostUpdate()
{
	Enemy::PostUpdate();
	_prepared_input = { KEY_IDLE, KEY_IDLE, 0, 0 };
}

bool Royd::OnCollision(Collider& origin, Collider& other)
{
	if (other.type == PLAYER)
	{
		if (origin.type == ENEMY_ATTACK)
		{
			NPC* player = static_cast<NPC*>(other.attached);
			player->ReceiveAttack(damage);
			return false;
		}
		_touching_player = true;
		Target = other.attached;
	}

	return true;
}

void Royd::prepare_input(Input& input)
{
	input = _prepared_input;
}
