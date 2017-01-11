#ifndef __HOMER_REVIVE_H__
#define __HOMER_REVIVE_H__

#include "State.h"
#include "Point3.h"

namespace HomerFSM {

	class Revive :
		public State
	{
	public:
		Revive();
		~Revive();

		void Enter(NPC& player, const Input& input) override;
		State* HandleInput(NPC& player, const Input& input) override;
		State* Update(NPC& player, const Input& input) override;

	private:
		iPoint3 _position;
	};

}

#endif // __HOMER_REVIVE_H__
