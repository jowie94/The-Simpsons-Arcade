#ifndef __GENERIC_IDLE_H__
#define __GENERIC_IDLE_H__

#include "State.h"

namespace GenericFSM {

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

#endif // __GENERIC_IDLE_H__
