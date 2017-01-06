#ifndef __STATE_H__
#define __STATE_H__

class NPC;

class State
{
public:

	State()
	{}

	virtual ~State()
	{}

	virtual void Enter(NPC& player) = 0;
	virtual State* HandleInput(NPC& player) = 0;
	virtual State* Update(NPC& player) = 0;
};

#endif // __STATE_H__
