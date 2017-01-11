#ifndef __HOMER_DEAD_H__
#define __HOMER_DEAD_H__

#include "GenericDead.h"

namespace HomerFSM {

	class Dead :
		public GenericFSM::Dead
	{
	public:
		Dead();
		~Dead();

		void Enter(NPC& player, const Input& input) override;
		State* AnimationEnd(NPC& player) override;
	};

}

#endif // __HOMER_DEAD_H__
