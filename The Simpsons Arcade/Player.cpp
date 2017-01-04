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

	correct_position();

	Sprite* rect = &_current_animation.GetCurrentFrame();

	int positionX = Position.x;

	if (flip)
		positionX += rect->Pivot.x - rect->Rect.w + center;
	else
		positionX -= rect->Pivot.x;

	int positionY = Position.y + rect->Pivot.y;

	if (FeetCollider)
		FeetCollider->SetPos(positionX, positionY, Position.z);

	App->renderer->RelativeBlit(graphics, positionX, positionY, Position.z, &rect->Rect, 1.f, flip);
}

void Player::PostUpdate()
{
}

bool Player::CleanUp()
{
	_animations.clear();
	//RELEASE(_state);
	RELEASE(Idle);
	RELEASE(Walking);
	RELEASE(Jump);
	RELEASE(Attack);

	return true;
}

bool Player::OnCollision(Collider& origin, Collider& other)
{
	return true;
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
		LOG("Animation %s does not exist!", name.c_str());

	return ret;
}

SpriteAnimation* Player::CurrentAnimation()
{
	return &_current_animation;
}

void Player::SetDirection(int x)
{
	if (x)
		flip = x < 0;
}

bool Player::LooksRight() const
{
	return !flip;
}

void Player::SwitchState(State* newState)
{
	assert(newState != nullptr);

	_state = newState;
	_state->Enter(*this);
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
