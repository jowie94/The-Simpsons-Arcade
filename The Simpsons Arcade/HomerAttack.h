#ifndef __HOMER_ATTACK_H__
#define __HOMER_ATTACK_H__
#include "State.h"

namespace HomerFSM
{

	class Attack :
		public State
	{
	public:
		Attack();
		~Attack();

		void Enter(NPC& player) override;
		State* HandleInput(NPC& player) override;
		State* Update(NPC& player) override;

	private:
		int pushes = 0;
	};
}

#endif // __HOMER_ATTACK_H__
