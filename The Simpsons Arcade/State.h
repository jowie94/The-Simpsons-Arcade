#ifndef __STATE_H__
#define __STATE_H__

class Player;

class State
{
public:

	State()
	{}

	virtual ~State()
	{}

	virtual void Enter(Player& player) = 0;
	virtual State* HandleInput(Player& player) = 0;
	virtual State* Update(Player& player) = 0;
};

#endif // __STATE_H__
