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

	bool Start() override = 0;

	bool OnCollision(Collider& origin, Collider& other) override;

protected:
	void correct_position() override;
	void prepare_input(Input& input) override;
	static int calculate_damage();

	int player_number = 0;
};

#endif // __PLAYER_H__
