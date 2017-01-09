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

	Sprite* rect = &current_animation.GetCurrentFrame();

	int positionX = Position.x;
	int colliderX = Position.x;
	int attackX = Position.x;

	if (flip)
	{
		positionX += rect->Pivot.x - rect->Rect.w + center;
		colliderX = positionX;
		if (attack_collider)
			attackX = positionX;
	}
	else
	{
		positionX -= rect->Pivot.x;
		if (attack_collider)
			attackX += rect->Rect.w - attack_collider->rect.w;
	}

	int positionY = Position.y + rect->Pivot.y;

	if (FeetCollider)
		FeetCollider->SetPos(colliderX, Position.y + FeetCollider->rect.h, Position.z);

	if (attack_collider) // TODO: Correct collider position
		attack_collider->SetPos(attackX, Position.y + FeetCollider->rect.h, Position.z);

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
	RELEASE(Damaged);
	RELEASE(Dead);

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
		current_animation = it->second;
	else
		LOG("Animation %s does not exist!", name.c_str());

	return ret;
}

SpriteAnimation* NPC::CurrentAnimation()
{
	return &current_animation;
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
	assert(attack_collider == nullptr);

	Damage = INVINCIBLE;
	attack_collider = App->collision->AddCollider(FeetCollider->rect, this);
	attack_collider->type = PLAYER_ATTACK;
}

void NPC::FinishAttack()
{
	assert(attack_collider != nullptr);

	Damage = NONE;
	attack_collider->to_delete = true;
	attack_collider = nullptr;
}

void NPC::ReceiveAttack(int damage)
{
	if (Damage == NONE && Damage != INVINCIBLE)
	{
		life -= damage;
		Damage = damage == 1 && (rand() % 3 <= 2) ? SLIGHT : STRONG;

		if (Damaged)
			SwitchState(Damaged);
	}
}

void NPC::Die()
{
	if (FeetCollider)
		FeetCollider->to_delete = true;
}

bool NPC::IsAlive() const
{
	return life > 0;
}

void NPC::correct_position()
{
}

