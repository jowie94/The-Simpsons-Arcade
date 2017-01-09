#ifndef __ENEMY_DAMAGED_H__
#define __ENEMY_DAMAGED_H__

#include "GenericDamaged.h"

namespace EnemyFSM {

	class Damaged :
		public GenericFSM::Damaged
	{
	public:
		Damaged();
		~Damaged();

		void Enter(NPC& player, const Input& input) override;
	};

}

#endif // __ENEMY_DAMAGED_H__
