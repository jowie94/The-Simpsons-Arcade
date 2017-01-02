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

	void HandleInput();

	void AddAnimation(const string& name, const RectAnimation& animation);
	bool SetAnimation(const string& name);
	void SwitchState(State* newState);

protected:
	SDL_Texture* graphics = nullptr;
	RectAnimation _current_animation;

private:
	map<string, RectAnimation> _animations;
	State* _state = nullptr;

};

#endif // __PLAYER_H__
