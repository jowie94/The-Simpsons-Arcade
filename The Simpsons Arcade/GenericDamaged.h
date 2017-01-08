#ifndef __GENERIC_ATTACKED_H__
#define __GENERIC_ATTACKED_H__

#include "State.h"

namespace GenericFSM {

	class Damaged :
		public State
	{
	public:
		Damaged();
		~Damaged();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;

	private:
		bool get_up = false;
	};


}

#endif // __GENERIC_ATTACKED_H__
