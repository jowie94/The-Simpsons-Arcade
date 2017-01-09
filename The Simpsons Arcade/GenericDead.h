#ifndef __GENERIC_DEAD_H__
#define __GENERIC_DEAD_H__

#include "State.h"

namespace GenericFSM {

	class Dead :
		public State
	{
	public:
		Dead();
		~Dead();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;

		virtual State* AnimationEnd(NPC& player);
	};

}

#endif // __GENERIC_DEAD_H__
