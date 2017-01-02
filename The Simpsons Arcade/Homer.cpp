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

	RectAnimation idle;
	idle.frames.push_back({ 0, 5, 34, 64 });
	idle.frames.push_back({ 0, 5, 34, 64 });
	idle.frames.push_back({ 0, 5, 34, 64 });
	idle.frames.push_back({ 0, 5, 34, 64 });
	idle.frames.push_back({ 0, 5, 34, 64 });
	idle.frames.push_back({ 42, 6, 34, 64 });
	idle.frames.push_back({ 88, 6, 34, 64 });
	idle.frames.push_back({ 139, 6, 34, 64 });
	idle.speed = 0.1f;

	AddAnimation("idle", idle);

	SwitchState(new HomerFSM::Idle);

	return true;
}
