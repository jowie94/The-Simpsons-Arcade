#include "Royd.h"
#include "ModuleTextures.h"
#include "EnemyIdle.h"
#include "EnemyWalking.h"

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

	Idle = new EnemyFSM::Idle;
	Walking = new EnemyFSM::Walking;

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
		fPoint3 direction(vec.x, vec.y, vec.z);
		float distance = direction.Magnitude();
		direction = direction / distance;
		if (abs(vec.x) > 40)
			_prepared_input.x = direction.x < 0 ? floor(direction.x) : ceil(direction.x);
		if (abs(vec.z) > 5)
			_prepared_input.y = direction.z < 0 ? floor(direction.z) : ceil(direction.z);
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
	LOG("Collision!");

	if (other.type == PLAYER_ATTACK)
		LOG("Player attack");
	return true;
}

void Royd::prepare_input(Input& input)
{
	input = _prepared_input;
}
