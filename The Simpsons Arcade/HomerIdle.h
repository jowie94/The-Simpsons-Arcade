#ifndef __HOMER_IDLE_H__
#define __HOMER_IDLE_H__

#include "State.h"

namespace HomerFSM
{

	class Idle :
		public State
	{
	public:
		Idle();
		~Idle();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;
	};

}

#endif // __HOMER_IDLE_H__
