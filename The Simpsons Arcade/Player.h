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

protected:
	void correct_position() override;
};

#endif // __PLAYER_H__
