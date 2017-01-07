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

	SpriteAnimation idle;
	idle.frames.push_back({ { 16, 272, 33, 64 }, iPoint(4, 64) });

	AddAnimation("idle", idle);

	SpriteAnimation walk;
	walk.frames.push_back({ { 16, 32, 20, 64 }, iPoint(0, 64) });
	walk.frames.push_back({ { 64, 32, 25, 64 }, iPoint(4, 64) });
	walk.frames.push_back({ { 112, 33, 32, 63 }, iPoint(6, 63) });
	walk.frames.push_back({ { 160, 33, 24, 63 }, iPoint(3, 63) });
	walk.frames.push_back({ { 208, 33, 23, 63 }, iPoint(0, 63) });
	walk.frames.push_back({ { 256, 33, 27, 63 }, iPoint(3, 63) });
	walk.frames.push_back({ { 304, 34, 32, 62 }, iPoint(8, 62) });
	walk.frames.push_back({ { 352, 32, 24, 64 }, iPoint(3, 64) });
	walk.speed = 0.2f;

	AddAnimation("walk", walk);

	SpriteAnimation walk_up;
	walk_up.frames.push_back({ { 16, 114, 25, 62 }, iPoint(0, 62) });
	walk_up.frames.push_back({ { 64, 114, 27, 62 }, iPoint(0, 62) });
	walk_up.frames.push_back({ { 112, 114, 32, 62 }, iPoint(1, 62) });
	walk_up.frames.push_back({ { 160, 116, 27, 60 }, iPoint(0, 60) });
	walk_up.frames.push_back({ { 208, 115, 26, 61 }, iPoint(0, 61) });
	walk_up.frames.push_back({ { 256, 114, 28, 62 }, iPoint(2, 62) });
	walk_up.frames.push_back({ { 304, 115, 31, 61 }, iPoint(5, 61) });
	walk_up.frames.push_back({ { 352, 116, 25, 60 }, iPoint(0, 60) });
	walk_up.speed = 0.2f;

	AddAnimation("walk_up", walk_up);

	SpriteAnimation walk_down;
	walk_down.frames.push_back({ { 16, 192, 29, 64 }, iPoint(8, 64) });
	walk_down.frames.push_back({ { 64, 193, 25, 63 }, iPoint(4, 63) });
	walk_down.frames.push_back({ { 112, 194, 23, 62 }, iPoint(2, 61) });
	walk_down.frames.push_back({ { 160, 193, 24, 63 }, iPoint(3, 63) });
	walk_down.frames.push_back({ { 208, 192, 23, 64 }, iPoint(2, 64) });
	walk_down.frames.push_back({ { 256, 193, 25, 63 }, iPoint(6, 63) });
	walk_down.frames.push_back({ { 304, 194, 30, 62 }, iPoint(7, 62) });
	walk_down.frames.push_back({ { 352, 193, 39, 63 }, iPoint(11, 63) });
	walk_down.speed = 0.2f;

	AddAnimation("walk_down", walk_down);

	Idle = new EnemyFSM::Idle;
	Walking = new EnemyFSM::Walking;

	SwitchState(Idle);

	FeetCollider = App->collision->AddCollider(iRectangle3(0, 0, 0, 20, 10));
	FeetCollider->type = ENEMY;

	return graphics != nullptr;
}

void Royd::prepare_input(Input& input)
{
}
