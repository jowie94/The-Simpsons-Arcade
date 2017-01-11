#include "Homer.h"
#include "Engine.h"
#include "ModuleTextures.h"
#include "HomerIdle.h"
#include "HomerWalking.h"
#include "HomerJump.h"
#include "HomerAttack.h"
#include "HomerDamaged.h"
#include "HomerDead.h"
#include "HomerRevive.h"

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
	player_number = 0; // TODO: Change this number for the correct one
	life = 10;
	Speed = 2;

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
	walking.speed = 0.2f;

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
	walking_up.speed = 0.2f;

	AddAnimation("walk_up", walking_up);

	SpriteAnimation attack1;
	attack1.frames.push_back({ { 163, 163, 40, 63 }, iPoint(4, 63) });
	attack1.frames.push_back({ { 214, 164, 38, 62 }, iPoint(0, 62) });
	attack1.frames.push_back({ { 262, 164, 42, 62 }, iPoint(0, 62) });
	attack1.frames.push_back({ { 316, 163, 50, 63 }, iPoint(0, 63) });
	attack1.frames.push_back({ { 377, 164, 48, 62 }, iPoint(0, 62) });
	attack1.frames.push_back({ { 436, 163, 38, 63 }, iPoint(2, 63) });
	attack1.frames.push_back({ { 487, 163, 36, 63 }, iPoint(0, 63) });
	attack1.frames.push_back({ { 534, 164, 47, 62 }, iPoint(0, 62) });
	attack1.speed = 0.4f;

	AddAnimation("attack1", attack1);

	SpriteAnimation attack2;
	attack2.frames.push_back({ { 4, 163, 40, 63 }, iPoint(7, 63) });
	attack2.frames.push_back({ { 60, 163, 41, 63 }, iPoint(4, 63) });
	attack2.frames.push_back({ { 112, 164, 41, 62 }, iPoint(9, 62) });
	attack2.speed = 0.2f;

	AddAnimation("attack2", attack2);

	SpriteAnimation attack3 = attack2;
	attack3.frames.push_back({ { 591, 164, 56, 67 }, iPoint(0, 66) });
	attack3.frames.push_back({ { 660, 152, 35, 74 }, iPoint(0, 74) });
	attack2.speed = 0.4f;

	AddAnimation("attack3", attack3);

	SpriteAnimation jump_up;
	jump_up.frames.push_back({ { 8, 239, 41, 64 }, iPoint(10, 64) });
	jump_up.speed = 0.2f;
	jump_up.loop = false;

	AddAnimation("jump_up", jump_up);

	SpriteAnimation falling;
	falling.frames.push_back({ { 60, 237, 44, 66 }, iPoint(16, 65) });
	falling.loop = false;
	falling.speed = 0.1f;

	AddAnimation("falling", falling);

	SpriteAnimation air_attack1;
	air_attack1.frames.push_back({ { 125, 239, 48, 56 }, iPoint(14, 56) });
	air_attack1.frames.push_back({ { 191, 238, 48, 57 }, iPoint(9, 57) });
	air_attack1.speed = 0.2f;
	air_attack1.loop = false;

	AddAnimation("air_attack1", air_attack1);

	SpriteAnimation air_attack2;
	air_attack2.frames.push_back({ { 257, 264, 63, 39 }, iPoint(25, 39) });
	air_attack2.speed = 0.2f;
	air_attack2.loop = false;

	AddAnimation("air_attack2", air_attack2);

	SpriteAnimation damaged_0;
	damaged_0.frames.push_back({ { 15, 2207, 34, 63 }, iPoint(6, 63) });
	damaged_0.frames.push_back({ { 64, 2207, 31, 63 }, iPoint(3, 63) });
	damaged_0.speed = 0.1f;
	damaged_0.loop = false;

	AddAnimation("damaged_0", damaged_0);

	SpriteAnimation damaged_1;
	damaged_0.frames.push_back({ { 61, 2296, 39, 56 }, iPoint(-3, 56) });
	damaged_1.frames.push_back({ { 106, 2237, 60, 34 }, iPoint(38, 44) });
	damaged_1.frames.push_back({ { 179, 2237, 62, 30 }, iPoint(38, 28) });
	damaged_1.frames.push_back({ { 258, 2221, 40, 43 }, iPoint(29, 43) });
	damaged_1.frames.push_back({ { 311, 2208, 29, 55 }, iPoint(-9, 55) });
	damaged_1.speed = 0.1f;
	damaged_1.loop = false;

	AddAnimation("damaged_1", damaged_1);

	SpriteAnimation damaged_dead;
	damaged_dead.frames.push_back({ { 61, 2296, 39, 56 }, iPoint(-3, 56) });
	damaged_dead.frames.push_back({ { 106, 2237, 60, 34 }, iPoint(38, 44) });
	damaged_dead.frames.push_back({ { 179, 2237, 62, 30 }, iPoint(38, 28) });
	damaged_dead.speed = 0.1f;
	damaged_dead.loop = false;

	AddAnimation("damaged_dead", damaged_dead);

	SpriteAnimation dead;
	dead.frames.push_back({ { 279, 2406, 56, 39 }, iPoint(26, 39) });
	dead.frames.push_back({ { 279, 2406, 0, 0 }, iPoint(0, 39) });
	dead.frames.push_back({ { 353, 2417, 62, 29 }, iPoint(26, 29) });
	dead.frames.push_back({ { 353, 2417, 0, 0 }, iPoint(0, 29) });
	dead.frames.push_back({ { 353, 2417, 62, 29 }, iPoint(26, 29) });
	dead.frames.push_back({ { 279, 2406, 0, 0 }, iPoint(0, 39) });
	dead.frames.push_back({ { 353, 2417, 62, 29 }, iPoint(26, 29) });
	dead.frames.push_back({ { 353, 2417, 0, 0 }, iPoint(0, 29) });
	dead.speed = 0.2f;
	dead.loop = false;
	
	AddAnimation("dead", dead);

	Idle = new HomerFSM::Idle;
	Walking = new HomerFSM::Walking;
	Jump = new HomerFSM::Jump;
	Attack = new HomerFSM::Attack;
	Damaged = new HomerFSM::Damaged;
	Dead = new HomerFSM::Dead;
	Revive = new HomerFSM::Revive;

	SwitchState(Idle);

	FeetCollider = App->collision->AddCollider(iRectangle3(0, 0, 0, 30, 10), this);
	FeetCollider->type = PLAYER;
	NPC::Revive();

	return true;
}
