#include "Player.h"
#include "Engine.h"
#include "ModuleRender.h"


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
	SDL_Rect* rect = &_current_animation.GetCurrentFrame();
	App->renderer->Blit(graphics, _position.x + (rect->w / 2), _position.y, _position.z, rect);
}

void Player::PostUpdate()
{
}

bool Player::CleanUp()
{
	_animations.clear();
	return true;
}

bool Player::OnCollision(Collider& origin, Collider& other)
{
	return true;
}

void Player::HandleInput()
{
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
