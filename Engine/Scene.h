#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Entity.h"
#include <memory>

class Scene : public Module
{
public:
	Scene(bool active) : Module(active)
	{
		xmin = xmax = zmin = zmax = 0;
	}

	virtual ~Scene() {}

	void AddEntity(Entity* entity)
	{
		_entities.push_back(entity);
	}

	void RemoveEntity(Entity* entity)
	{
		_entities.remove(entity);
	}

	void AddPlayer(Entity* player)
	{
		//player->Position.y = 100; // TODO: Calculate correct position
		_players.push_back(player);
	}

	void RemovePlayer(Entity* player)
	{
		_players.remove(player);
	}

	void PlayerList(std::list<Entity*>& players) const
	{
		players = _players;
	}

	void AddEnemy(Entity* enemy)
	{
		if (enemy->IsEnabled())
			enemy->Start();
		else
			enemy->Enable();
		_enemies.push_back(enemy);
	}

	void RemoveEnemy(Entity* enemy)
	{
		_enemies.remove(enemy);
	}

	bool Start() override
	{
		return StartAllEntities();
	}

	update_status PreUpdate() override
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->PreUpdate();

		for (auto it = _players.begin(); it != _players.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->PreUpdate();

		for (auto it = _enemies.begin(); it != _enemies.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->PreUpdate();

		return UPDATE_CONTINUE;
	}

	update_status Update() override
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->Update();

		for (auto it = _players.begin(); it != _players.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->Update();

		for (auto it = _enemies.begin(); it != _enemies.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->Update();

		return UPDATE_CONTINUE;
	}

	update_status PostUpdate() override
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->PostUpdate();

		for (auto it = _players.begin(); it != _players.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->PostUpdate();

		for (auto it = _enemies.begin(); it != _enemies.end(); ++it)
			if ((*it)->IsEnabled())
				(*it)->PostUpdate();

		return UPDATE_CONTINUE;
	}

	bool CleanUp() override
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			(*it)->CleanUp();
			RELEASE((*it));
		}
		_entities.clear();

		for (auto it = _players.begin(); it != _players.end(); ++it)
		{
			(*it)->CleanUp();
			RELEASE((*it));
		}
		_players.clear();

		for (auto it = _enemies.begin(); it != _enemies.end(); ++it)
		{
			(*it)->CleanUp();
			RELEASE((*it));
		}
		_players.clear();

		return true;
	}

	virtual void SceneLimits(std::pair<int, int>& x, std::pair<int, int>& z) const
	{
		x = std::make_pair(xmin, xmax);
		z = std::make_pair(zmin, zmax);
	}

	void EnemyDefeated()
	{
		++enemies_defeated;
	}

	virtual bool Finished() const
	{
		return false;
	}

	virtual bool GameOver() const
	{
		return false;
	}

protected:
	std::list<Entity*> _entities;
	std::list<Entity*> _players;
	std::list<Entity*> _enemies;

	int xmin, xmax, zmin, zmax;
	int enemies_defeated = 0;

private:
	bool StartAllEntities() const
	{
		bool ret = true;

		for (auto it = _entities.cbegin(); it != _entities.cend() && ret; ++it)
		{
			if ((*it)->IsEnabled())
				ret = (*it)->Start();
		}

		for (auto it = _players.cbegin(); it != _players.cend() && ret; ++it)
		{
			if ((*it)->IsEnabled())
				ret = (*it)->Start();
		}

		for (auto it = _enemies.cbegin(); it != _enemies.cend() && ret; ++it)
		{
			if ((*it)->IsEnabled())
				ret = (*it)->Start();
		}

		return ret;
	}

};

#endif // __SCENE_H__
