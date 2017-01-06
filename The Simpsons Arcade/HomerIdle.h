#ifndef __HOMER_IDLE_H__
#define __HOMER_IDLE_H__

#include "GenericIdle.h"

namespace HomerFSM
{

	class Idle :
		public GenericFSM::Idle
	{
	public:
		Idle();
		~Idle();
	};

}

#endif // __HOMER_IDLE_H__
