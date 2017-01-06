#ifndef __HOMER_WALKING_H__
#define __HOMER_WALKING_H__

#include "GenericWalking.h"

namespace HomerFSM 
{

	class Walking :
		public GenericFSM::Walking
	{
	public:
		Walking();
		~Walking();

		State* HandleInput(NPC& player, const Input& input) override;

	private:
		bool up = false;
	};

}

#endif // __HOMER_WALKING_H__
