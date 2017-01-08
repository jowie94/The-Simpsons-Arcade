#include "NPC.h"
#include <cassert>
#include "ModuleSceneManager.h"
#include "Scene.h"
#include "State.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::PreUpdate()
{
	prepare_input(_last_input);
	State* newState = _state->HandleInput(*this, _last_input);

	if (newState)
		SwitchState(newState);
}

void NPC::Update()
{
	State* newState = _state->Update(*this, _last_input);

	if (newState)
		SwitchState(newState);

	correct_position();

	Sprite* rect = &_current_animation.GetCurrentFrame();

	int positionX = Position.x;
	int colliderX = Position.x;
	int attackX = Position.x;

	if (flip)
	{
		positionX += rect->Pivot.x - rect->Rect.w + center;
		colliderX = positionX;
		
	}
	else
	{
		positionX -= rect->Pivot.x;
		if (_attack_collider)
			attackX += (rect->Rect.w - _attack_collider->rect.w);
	}

	int positionY = Position.y + rect->Pivot.y;

	if (FeetCollider)
		FeetCollider->SetPos(colliderX, Position.y + FeetCollider->rect.h, Position.z);

	if (_attack_collider) // TODO: Correct collider position
		_attack_collider->SetPos(attackX, Position.y + FeetCollider->rect.h, Position.z);

	App->renderer->Blit(graphics, positionX, positionY, Position.z, &rect->Rect, 1.f, flip);
}

void NPC::PostUpdate()
{
}

bool NPC::CleanUp()
{
	_animations.clear();
	//RELEASE(_state);
	RELEASE(Idle);
	RELEASE(Walking);
	RELEASE(Jump);
	RELEASE(Attack);

	return true;
}

bool NPC::OnCollision(Collider& origin, Collider& other)
{
	return true;
}

void NPC::AddAnimation(const string& name, const SpriteAnimation& animation)
{
	_animations[name] = animation;
}

bool NPC::SetAnimation(const string& name)
{
	auto it = _animations.find(name);

	bool ret = it != _animations.end();

	if (ret)
		_current_animation = it->second;
	else
		LOG("Animation %s does not exist!", name.c_str());

	return ret;
}

SpriteAnimation* NPC::CurrentAnimation()
{
	return &_current_animation;
}

void NPC::SetDirection(int x)
{
	if (x)
		flip = x < 0;
}

bool NPC::LooksRight() const
{
	return !flip;
}

void NPC::SwitchState(State* newState)
{
	assert(newState != nullptr);

	_state = newState;
	_state->Enter(*this, _last_input);
}

void NPC::BeginAttack()
{
	assert(_attack_collider == nullptr);

	_attack_collider = App->collision->AddCollider(FeetCollider->rect, this);
	_attack_collider->type = PLAYER_ATTACK;
}

void NPC::FinishAttack()
{
	assert(_attack_collider != nullptr);

	_attack_collider->to_delete = true;
	_attack_collider = nullptr;
}

void NPC::ReceiveAttack(int damage)
{
	if (!IsDamaged)
	{
		life -= damage;

		if (Damaged)
			SwitchState(Damaged);
	}
}

bool NPC::IsAlive() const
{
	return life > 0;
}

void NPC::correct_position()
{
}

