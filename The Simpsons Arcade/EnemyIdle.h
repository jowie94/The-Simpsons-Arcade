#ifndef __ENEMY_IDLE_H__
#define __ENEMY_IDLE_H__

#include "GenericIdle.h"

namespace EnemyFSM 
{

	class Idle :
		public GenericFSM::Idle
	{
	public:
		Idle();
		~Idle();
	};

}

#endif // __ENEMY_IDLE_H__
