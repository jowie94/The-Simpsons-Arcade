#ifndef __HOMER_DAMAGED_H__
#define __HOMER_DAMAGED_H__

#include "GenericDamaged.h"

namespace HomerFSM {

	class Damaged :
		public GenericFSM::Damaged
	{
	public:
		Damaged();
		~Damaged();

		void Enter(NPC& player, const Input& input) override;
	};

}

#endif // __HOMER_DAMAGED_H__
