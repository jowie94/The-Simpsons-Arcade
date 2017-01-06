#include "Royd.h"
#include "ModuleTextures.h"
#include "EnemyIdle.h"

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

	Idle = new EnemyFSM::Idle;

	SwitchState(Idle);

	FeetCollider = App->collision->AddCollider(iRectangle3(0, 0, 0, 20, 10));
	FeetCollider->type = ENEMY;

	return graphics != nullptr;
}

void Royd::prepare_input(Input& input)
{
}
