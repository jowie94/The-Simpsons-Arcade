#ifndef __HOMER_ATTACK_H__
#define __HOMER_ATTACK_H__

#include "GenericAttack.h"

namespace HomerFSM
{

	class Attack :
		public GenericFSM::Attack
	{
	public:
		Attack();
		~Attack();
	};
}

#endif // __HOMER_ATTACK_H__
