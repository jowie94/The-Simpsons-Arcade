#ifndef __HOMER_JUMP_H__
#define __HOMER_JUMP_H__

#include "State.h"
#include "HomerWalking.h"

namespace HomerFSM {

	class Jump : public Walking
	{
	public:
		Jump();
		~Jump();

		void Enter(NPC& player) override;
		State* HandleInput(NPC& player) override;
		State* Update(NPC& player) override;

	private:
		bool ascending;
		float speed;
	};

}

#endif // __HOMER_JUMP_H__
