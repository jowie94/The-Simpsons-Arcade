#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"
#include <map>

class State;
struct SDL_Texture;

class Player :
	public Entity
{
public:
	Player();
	virtual ~Player();

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

	State* Idle = nullptr;
	State* Walking = nullptr;
	State* Jump = nullptr;
	State* Attack = nullptr;

protected:
	SDL_Texture* graphics = nullptr;
	SpriteAnimation _current_animation;
	bool flip = false;
	int center = 0;

private:
	void correct_position();

	map<string, SpriteAnimation> _animations;
	State* _state = nullptr;

};

#endif // __PLAYER_H__
