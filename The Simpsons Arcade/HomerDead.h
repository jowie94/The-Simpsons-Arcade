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

		State* AnimationEnd(NPC& player) override;
	};

}

#endif // __HOMER_DEAD_H__
