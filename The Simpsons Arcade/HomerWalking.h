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

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;

	private:
		bool up = false;
	};

}

#endif // __HOMER_WALKING_H__
