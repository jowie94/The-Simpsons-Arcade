#ifndef __NPC_H__
#define __NPC_H__

#include "Entity.h"
#include "Animation.h"
#include <map>
#include "Input.h"

class State;

class NPC :
	public Entity
{
public:
	enum DamageType
	{
		NONE,
		SLIGHT,
		STRONG
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
	void BeginAttack();
	void FinishAttack();
	void ReceiveAttack(int damage);
	bool IsAlive() const;

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
	SpriteAnimation _current_animation;
	bool flip = false;
	virtual void correct_position();
	int center = 0;
	int life = 0;

	virtual void prepare_input(Input& input) = 0;

private:
	map<string, SpriteAnimation> _animations;
	State* _state = nullptr;
	Collider* _attack_collider = nullptr;
	Input _last_input;
};

#endif // __NPC_H__
