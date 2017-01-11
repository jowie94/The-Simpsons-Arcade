#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"
#include "Animation.h"
#include <map>
#include "Input.h"
#include "ModuleTimer.h"

class State;

class NPC :
	public Entity
{
public:
	enum DamageType
	{
		NONE,
		SLIGHT,
		STRONG,
		INVINCIBLE
	};

	NPC();
	virtual ~NPC();

	bool Start() override = 0;
	void PreUpdate() override;
	void Update() override;
	void PostUpdate() override;
	bool CleanUp() override;
	bool OnCollision(Collider& origin, Collider& other) override;

	void AddAnimation(const string& name, const SpriteAnimation& animation);
	bool SetAnimation(const string& name);
	SpriteAnimation* CurrentAnimation();
	void SetDirection(int x);
	bool LooksRight() const;
	void SwitchState(State* newState);
	virtual void BeginAttack();
	virtual void FinishAttack();
	void ReceiveAttack(int damage);
	virtual void Die();
	bool IsAlive() const;
	void Revive();

public:
	State* Idle = nullptr;
	State* Walking = nullptr;
	State* Jump = nullptr;
	State* Attack = nullptr;
	State* Damaged = nullptr;
	State* Dead = nullptr;

	DamageType Damage = NONE;
	int Speed = 1;

protected:
	SDL_Texture* graphics = nullptr;
	SpriteAnimation current_animation;
	bool flip = false;
	virtual void correct_position();
	int center = 0;
	int life = 0;
	Collider* attack_collider = nullptr;

	virtual void prepare_input(Input& input) = 0;

private:
	map<string, SpriteAnimation> _animations;
	State* _state = nullptr;
	Input _last_input;

	ModuleTimer::Timer* _revive_timer = nullptr;
	int _draw = 0;
};

#endif // __NPC_H__
