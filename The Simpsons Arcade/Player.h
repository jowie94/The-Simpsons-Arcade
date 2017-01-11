#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include "NPC.h"

class State;
struct SDL_Texture;

class Player :
	public NPC
{
public:
	Player();
	virtual ~Player();

	bool Start() override;
	void Update() override;
	bool CleanUp() override;

	bool OnCollision(Collider& origin, Collider& other) override;
	void Die() override;

	int Lifes = 0;

	State* Revive = nullptr;
	State* Win = nullptr;
	int FxDizzy = -1;

protected:
	void correct_position() override;
	void prepare_input(Input& input) override;
	static int calculate_damage();

	int player_number = 0;
	bool _win = false;
};

#endif // __PLAYER_H__
