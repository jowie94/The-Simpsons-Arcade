#include "Player.h"
#include "Engine.h"
#include "ModuleRender.h"
#include <cassert>
#include "State.h"
#include "ModuleInput.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::PreUpdate()
{
	State* newState = _state->HandleInput(*this);

	if (newState)
		SwitchState(newState);
}

void Player::Update()
{
	State* newState = _state->Update(*this);
	
	if (newState)
		SwitchState(newState);

	Sprite* rect = &_current_animation.GetCurrentFrame();

	int positionX = Position.x;

	if (flip)
		positionX += rect->Pivot.x - rect->Rect.w + center;
	else
		positionX -= rect->Pivot.x;

	App->renderer->RelativeBlit(graphics, positionX, Position.y + rect->Pivot.y, Position.z, &rect->Rect, 1.f, flip);
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

void Player::AddAnimation(const string& name, const SpriteAnimation& animation)
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

void Player::SetDirection(int x)
{
	flip = x < 0;
}

void Player::SwitchState(State* newState)
{
	assert(newState != nullptr);

	RELEASE(_state);
	_state = newState;
	_state->Enter(*this);
}
