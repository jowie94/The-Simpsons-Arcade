#ifndef __HOMER_WIN_H__
#define __HOMER_WIN_H__

#include "State.h"

namespace HomerFSM {

	class Win :
		public State
	{
	public:
		Win();
		~Win();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;
	};

}

#endif // __HOMER_WIN_H__
