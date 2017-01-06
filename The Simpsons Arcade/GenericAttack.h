#ifndef __GENERIC_ATTACK_H__
#define __GENERIC_ATTACK_H__

#include "State.h"

namespace GenericFSM {

	class Attack :
		public State
	{
	public:
		Attack();
		~Attack();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;

	private:
		int pushes = 0;
	};

}

#endif // __GENERIC_ATTACK_H__
