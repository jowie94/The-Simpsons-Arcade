#ifndef __GENERIC_JUMP_H__
#define __GENERIC_JUMP_H__

#include "State.h"
#include "GenericWalking.h"

namespace GenericFSM {

	class Jump :
		public Walking
	{
	public:
		Jump();
		~Jump();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;

	private:
		bool ascending;
		float speed;
	};

}

#endif // __GENERIC_JUMP_H__

