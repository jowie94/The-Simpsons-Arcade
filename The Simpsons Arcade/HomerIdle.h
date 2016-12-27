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

		void Enter(Player& player) override;
		State* HandleInput(Player& player) override;
		State* Update(Player& player) override;
	};

}

#endif // __HOMER_IDLE_H__
