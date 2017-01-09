#ifndef __ENEMY_ATTACK_H__
#define __ENEMY_ATTACK_H__

#include "GenericAttack.h"

namespace EnemyFSM {

	class Attack :
		public GenericFSM::Attack
	{
	public:
		Attack();
		~Attack();
	};

}

#endif // __ENEMY_ATTACK_H__
