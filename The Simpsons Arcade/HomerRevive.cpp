#include "HomerRevive.h"
#include "NPC.h"
#include "ModuleSceneManager.h"
#include "Scene.h"

HomerFSM::Revive::Revive()
{
}

HomerFSM::Revive::~Revive()
{
}

void HomerFSM::Revive::Enter(NPC& player, const Input& input)
{
	player.SetAnimation("revive");
	player.Damage = NPC::REVIVING;
	player.SetDirection(1);
	player.Position.y = 40;
	pair<int, int> ignore;
	App->scene_manager->CurrentScene()->SceneLimits(_limits, ignore);

	player.Position.x = _limits.first;

	_down = false;
	_direction = 1;
}

State* HomerFSM::Revive::HandleInput(NPC& player, const Input& input)
{
	return nullptr;
}

State* HomerFSM::Revive::Update(NPC& player, const Input& input)
{
	if (!_down)
	{
		player.Position.x += 6 * _direction;
		if (player.Position.x >= _limits.second)
		{
			player.SetDirection(-1);
			_direction = -1;
		}
		if (player.Position.x <= _limits.first)
		{
			player.SetDirection(1);
			_down = true;
			player.SetAnimation("revive_down");
		}
	}
	else
	{
		player.Position.y -= 2;
	}

	if (_down && player.Position.y == 0)
	{
		player.Position.x = _limits.first + 10;
		player.Position.y = 0;
		player.Revive();
		player.Damage = NPC::NONE;
		return player.Idle;
	}
	
	return nullptr;
}
