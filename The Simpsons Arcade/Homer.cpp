#include "Homer.h"
#include "Engine.h"
#include "ModuleTextures.h"
#include "HomerIdle.h"


Homer::Homer()
{
}


Homer::~Homer()
{
}

bool Homer::Start()
{
	SDL_Color key = { 89, 253, 66, 0 };
	graphics = App->textures->Load("Simpsons/homer.png", &key);
	center = 12; // Homer's center

	SpriteAnimation idle;
	idle.frames.push_back({ { 6, 5, 25, 64 }, iPoint(0, 64) });
	idle.frames.push_back({ { 6, 5, 25, 64 }, iPoint(0, 64) });
	idle.frames.push_back({ { 6, 5, 25, 64 }, iPoint(0, 64) });
	idle.frames.push_back({ { 6, 5, 25, 64 }, iPoint(0, 64) });
	idle.frames.push_back({ { 6, 5, 25, 64 }, iPoint(0, 64) });
	idle.frames.push_back({ { 6, 5, 25, 64 }, iPoint(0, 64) });
	idle.frames.push_back({ { 45, 6, 32, 64 }, iPoint(4, 64) });
	idle.frames.push_back({ { 88, 6, 34, 64 }, iPoint(7, 64) });
	idle.frames.push_back({ { 142, 7, 29, 63 }, iPoint(4, 63) });
	idle.speed = 0.1f;

	AddAnimation("idle", idle);

	SpriteAnimation walking;
	walking.frames.push_back({ { 191, 7, 28, 63 }, iPoint(1, 63) });
	walking.frames.push_back({ { 241, 7, 34, 63 }, iPoint(2, 63) });
	walking.frames.push_back({ { 290, 7, 30, 62 }, iPoint(4, 64) });
	walking.frames.push_back({ { 340, 6, 24, 63 }, iPoint(0, 65) });
	walking.frames.push_back({ { 382, 7, 25, 62 }, iPoint(0, 64) });
	walking.frames.push_back({ { 428, 7, 33, 63 }, iPoint(1, 63) });
	walking.frames.push_back({ { 478, 6, 24, 64 }, iPoint(0, 64) });
	walking.frames.push_back({ { 519, 6, 24, 64 }, iPoint(0, 64) });
	walking.speed = 0.1f;

	AddAnimation("walk", walking);

	SpriteAnimation walking_up;
	walking_up.frames.push_back({ { 7, 83, 29, 63 }, iPoint(0, 63) });
	walking_up.frames.push_back({ { 48, 84, 28, 62 }, iPoint(0, 62) });
	walking_up.frames.push_back({ { 88, 83, 25, 61 }, iPoint(0, 62) });
	walking_up.frames.push_back({ { 128, 82, 25, 62 }, iPoint(0, 64) });
	walking_up.frames.push_back({ { 169, 83, 33, 62 }, iPoint(0, 63) });
	walking_up.frames.push_back({ { 221, 84, 27, 62 }, iPoint(0, 62) });
	walking_up.frames.push_back({ { 266, 83, 27, 63 }, iPoint(0, 63) });
	walking_up.frames.push_back({ { 307, 82, 29, 63 }, iPoint(1, 61) });
	walking_up.speed = 0.1f;

	AddAnimation("walk_up", walking_up);

	SpriteAnimation attack1;
	attack1.frames.push_back({ { 163, 163, 40, 63 }, iPoint(7, 63) });
	attack1.frames.push_back({ { 214, 164, 38, 62 }, iPoint(5, 62) });
	attack1.frames.push_back({ { 262, 164, 42, 62 }, iPoint(7, 62) });
	attack1.frames.push_back({ { 316, 163, 50, 63 }, iPoint(11, 63) });
	attack1.frames.push_back({ { 377, 164, 48, 62 }, iPoint(9, 62) });
	attack1.speed = 0.5f;

	AddAnimation("attack1", attack1);

	SpriteAnimation attack2;
	attack2.frames.push_back({ { 4, 163, 40, 63 }, iPoint(7, 63) });
	attack2.frames.push_back({ { 60, 163, 41, 63 }, iPoint(4, 63) });
	attack2.frames.push_back({ { 112, 164, 41, 62 }, iPoint(9, 62) });
	attack2.speed = 0.5f;

	AddAnimation("attack2", attack2);

	SwitchState(new HomerFSM::Idle);

	return true;
}
