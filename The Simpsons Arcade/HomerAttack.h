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

		void Enter(Player& player) override;
		State* HandleInput(Player& player) override;
		State* Update(Player& player) override;

	private:
		static int pushes;
	};
}

#endif // __HOMER_ATTACK_H__
