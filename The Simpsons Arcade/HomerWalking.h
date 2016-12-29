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

		void Enter(Player& player) override;
		State* HandleInput(Player& player) override;
		State* Update(Player& player) override;
	};

}

#endif // __HOMER_WALKING_H__
