#ifndef __ENEMY_WALKING_H__
#define __ENEMY_WALKING_H__

#include "GenericWalking.h"
#include "Point3.h"

namespace EnemyFSM {

	class Walking :
		public GenericFSM::Walking
	{
	public:
		Walking();
		~Walking();

		State* Update(NPC& player, const Input& input) override;

	private:
		iPoint3::Side _last_side;
	};

}

#endif // __ENEMY_WALKING_H__
