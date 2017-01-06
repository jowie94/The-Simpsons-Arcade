#pragma once
#include "Entity.h"
#include "Animation.h"
#include <map>

class State;

class NPC :
	public Entity
{
public:
	NPC();
	~NPC();

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

public:
	State* Idle = nullptr;
	State* Walking = nullptr;
	State* Jump = nullptr;
	State* Attack = nullptr;

protected:
	SDL_Texture* graphics = nullptr;
	SpriteAnimation _current_animation;
	bool flip = false;
	virtual void correct_position();
	int center = 0;

private:
	map<string, SpriteAnimation> _animations;
	State* _state = nullptr;
	Collider* _attack_collider = nullptr;
};

