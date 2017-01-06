#ifndef __GENERIC_WALK_H__
#define __GENERIC_WALK_H__

#include "State.h"

namespace GenericFSM {

	class Walking :
		public State
	{
	public:
		Walking();
		~Walking();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;
	};

}

#endif // __GENERIC_WALK_H__
