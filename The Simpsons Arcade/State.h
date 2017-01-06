#ifndef __STATE_H__
#define __STATE_H__

struct Input;
class NPC;

class State
{
public:

	State()
	{}

	virtual ~State()
	{}

	virtual void Enter(NPC& player, const Input& input) = 0;
	virtual State* HandleInput(NPC& player, const Input& input) = 0;
	virtual State* Update(NPC& player, const Input& input) = 0;
};

#endif // __STATE_H__
