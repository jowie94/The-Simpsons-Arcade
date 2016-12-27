#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"
#include <map>

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

	void AddAnimation(const string& name, const Animation& animation);
	bool SetAnimation(const string& name);

protected:
	SDL_Texture* graphics;
	Animation _current_animation;
	// TODO: State machine goes here

private:
	map<string, Animation> _animations;
};

#endif // __PLAYER_H__
