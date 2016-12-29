#include "Player.h"
#include "Engine.h"
#include "ModuleRender.h"
#include <cassert>
#include "State.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::PreUpdate()
{
}

void Player::Update()
{
	State* newState = _state->Update(*this);
	
	if (newState)
		SwitchState(newState);

	SDL_Rect* rect = &_current_animation.GetCurrentFrame();
	App->renderer->RelativeBlit(graphics, Position.x, Position.y + rect->h, Position.z, rect);
}

void Player::PostUpdate()
{
}

bool Player::CleanUp()
{
	_animations.clear();
	RELEASE(_state);

	return true;
}

bool Player::OnCollision(Collider& origin, Collider& other)
{
	return true;
}

void Player::HandleInput()
{
	State* newState = _state->HandleInput(*this);
	
	if (newState)
		SwitchState(newState);
}

void Player::AddAnimation(const string& name, const Animation& animation)
{
	_animations[name] = animation;
}

bool Player::SetAnimation(const string& name)
{
	auto it = _animations.find(name);

	bool ret = it != _animations.end();

	if (ret)
		_current_animation = it->second;
	else
		LOG("Animation %s does not exist!", name);

	return ret;
}

void Player::SwitchState(State* newState)
{
	assert(newState != nullptr);

	RELEASE(_state);
	_state = newState;
	_state->Enter(*this);
}
