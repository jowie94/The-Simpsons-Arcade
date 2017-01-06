#ifndef __HOMER_JUMP_H__
#define __HOMER_JUMP_H__

#include "GenericJump.h"

namespace HomerFSM {

	class Jump : 
		public GenericFSM::Jump
	{
	public:
		Jump();
		~Jump();
	};

}

#endif // __HOMER_JUMP_H__
