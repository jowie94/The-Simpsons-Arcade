#include "Player.h"
#include "Engine.h"
#include "ModuleRender.h"
#include <cassert>
#include "State.h"
#include "ModuleInput.h"
#include "Scene.h"
#include "ModuleSceneManager.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::correct_position()
{
	pair<int, int> x, z;

	App->scene_manager->CurrentScene()->SceneLimits(x, z);

	if (Position.x < x.first)
		Position.x = x.first;
	else if (Position.x > x.second)
		Position.x = x.second;

	if (Position.z < z.first)
		Position.z = z.first;
	else if (Position.z > z.second)
		Position.z = z.second;
}

void Player::prepare_input(Input& input)
{
	input.x = App->input->GetAxis(player_number, X);
	input.y = App->input->GetAxis(player_number, Y);

	input.attack = App->input->GetKey(SDL_SCANCODE_Z);
	input.jump = App->input->GetKey(SDL_SCANCODE_X);
}
