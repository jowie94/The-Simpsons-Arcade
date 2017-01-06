#ifndef __ENEMY_WALKING_H__
#define __ENEMY_WALKING_H__

#include "GenericWalking.h"

namespace EnemyFSM {

	class Walking :
		public GenericFSM::Walking
	{
	public:
		Walking();
		~Walking();

		State* Update(NPC& player, const Input& input) override;
	};

}

#endif // __ENEMY_WALKING_H__
