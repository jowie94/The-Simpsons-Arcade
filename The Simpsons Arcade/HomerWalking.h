#ifndef __HOMER_WALKING_H__
#define __HOMER_WALKING_H__

#include "State.h"

namespace HomerFSM 
{

	class Walking :
		public State
	{
	public:
		Walking();
		~Walking();

		void Enter(NPC& player) override;
		State* HandleInput(NPC& player) override;
		State* Update(NPC& player) override;

	private:
		bool up = false;
	};

}

#endif // __HOMER_WALKING_H__
