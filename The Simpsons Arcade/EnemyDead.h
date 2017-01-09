#ifndef __ENEMY_DEAD_H__
#define __ENEMY_DEAD_H__

#include "GenericDead.h"

namespace EnemyFSM {

	class Dead :
		public GenericFSM::Dead
	{
	public:
		Dead();
		~Dead();

		State* AnimationEnd(NPC& player) override;
	};

}

#endif // __ENEMY_DEAD_H__
