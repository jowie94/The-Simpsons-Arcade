#include "FirstScene.h"
#include "Engine.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "EntityFactory.h"
#include "Player.h"
#include "ModuleSceneManager.h"
#include "Royd.h"
#include "ModuleAudio.h"
#include "GameOverScene.h"
#include "WinScene.h"

FirstScene::FirstScene(bool active) : Scene(active), _background(nullptr)
{
	xmin = 64 / SCREEN_SIZE + 10;
	xmax = 200;
	zmin = 10;
	zmax = 110;
}


FirstScene::~FirstScene()
{
}

bool FirstScene::Start()
{
	LOG("Loading first scene");

	SDL_Rect* camera = &App->renderer->camera;
	camera->x = -64;
	camera->y = -64;

	SDL_Color mask = { 86, 177, 222, 0 };

	_background = App->textures->Load("Simpsons/first_scene.png", &mask);
	_walls.x = _floor.x = _floor.y = 4;
	_walls.y = 264;
	_walls.w =_floor.w = 1663;
	_walls.h = _floor.h = 255;

	BaseFactory<Entity>* entityFactory = App->scene_manager->GetEntityFactory();

	Player* marge = entityFactory->GetObject<Player>(EntityFactory::MARGE);
	marge->Position.x = 70;
	marge->Position.z = 0;
	marge->PlayerNumber = 0;
	marge->Lifes = 3;
	AddPlayer(marge);

	Player* homer = entityFactory->GetObject<Player>(EntityFactory::HOMER);
	homer->Position.x = 70;
	homer->Position.z = 50;
	homer->PlayerNumber = 1;
	homer->Lifes = 3;
	AddPlayer(homer);

	Player* bart = entityFactory->GetObject<Player>(EntityFactory::BART);
	bart->Position.x = 60;
	bart->Position.z = 30;
	bart->PlayerNumber = 2;
	bart->Lifes = 3;
	AddPlayer(bart);

	Player* lisa = entityFactory->GetObject<Player>(EntityFactory::LISA);
	lisa->Position.x = 80;
	lisa->Position.z = 40;
	lisa->PlayerNumber = 3;
	lisa->Lifes = 3;
	AddPlayer(lisa);

	initialize_scene();

	Entity* ui = entityFactory->GetObject(EntityFactory::UI);
	AddEntity(ui);

	App->audio->PlayMusic("Simpsons/audio/129-Stage 1 - (Downtown Springfield).ogg");

	bool ret = Scene::Start();
	return ret;
}

update_status FirstScene::Update()
{
	// Draw everything --------------------------------------

	iPoint3 min(xmax, 0, zmax), max(0, 0, 0);

	for (Entity* entity : _players)
	{
		if (static_cast<Player*>(entity)->IsAlive())
		{
			iPoint3 pos = entity->Position;

			max.x = MAX(pos.x, max.x);
			max.z = MAX(pos.z, max.z);
			min.x = MIN(pos.x, min.x);
			min.z = MIN(pos.z, min.z);
		}
	}

	iPoint3 mid = (min + max) / 2;
	SDL_Rect* camera = &App->renderer->camera;

	int y = int(ZTOY(mid.z, App->renderer->RenderingAngle));
	camera->y = (y - _walls.h + SCREEN_HEIGHT - 20) * SCREEN_SIZE;

	camera->y = CLAMP(camera->y, (-_walls.h + SCREEN_HEIGHT) * SCREEN_SIZE, 0);

	int right_bound = -(camera->x) / SCREEN_SIZE + SCREEN_WIDTH - 150;
	if (mid.x >= right_bound && can_advance())
		camera->x -= 2 * SCREEN_SIZE;

	camera->x = CLAMP(camera->x, (-_walls.w + SCREEN_WIDTH) * SCREEN_SIZE, 0);

	xmin = -camera->x / SCREEN_SIZE + 16;
	xmax = -camera->x / SCREEN_SIZE + SCREEN_WIDTH - 50;

	if (!_stages.empty())
	{
		PILE stage = _stages.front();
		if (stage.first <= abs(camera->x) / SCREEN_SIZE)
		{
			for (Entity* entity : *stage.second)
			{
				AddEnemy(entity);
			}

			RELEASE(stage.second);
			_stages.pop();
		}
	}
	else if (Finished())
	{
		if (!_end_timer)
		{
			App->audio->PlayMusic("Simpsons/audio/150-Completed.ogg", 0.f, 0);
			_end_timer = App->timer->AddTimer(5 * 1000);
		}
		else if (_end_timer->finished)
		{
			App->scene_manager->SetScene(new WinScene(false));
			return UPDATE_CONTINUE;
		}
	}
	
	if (GameOver())
	{
		App->scene_manager->SetScene(new GameOverScene(false));
	}
	else
	{
		App->renderer->BlitBackground(_background, 0, 0, &_walls);
		App->renderer->BlitBackground(_background, 0, 0, &_floor);
		return Scene::Update();
	}

	return UPDATE_CONTINUE;
}

bool FirstScene::CleanUp()
{
	App->textures->Unload(_background);

	RELEASE(_end_timer);

	while (!_stages.empty())
	{
		PILE stage = _stages.front();

		for (Entity* entity : *stage.second)
		{
			entity->CleanUp();
			RELEASE(entity);
		}

		RELEASE(stage.second);
		_stages.pop();
	}

	return Scene::CleanUp();
}

bool FirstScene::Finished() const
{
	return _enemies.size() == enemies_defeated && _stages.empty();
}

bool FirstScene::GameOver() const
{
	bool over = false;

	for (auto it = _players.begin(); it != _players.end() && !over; ++it)
	{
		Player* npc = static_cast<Player*>(*it);
		over = !npc->IsAlive() && npc->Lifes < 0;
	}

	return over;
}

void FirstScene::initialize_scene()
{
	BaseFactory<Entity>* entityFactory = App->scene_manager->GetEntityFactory();

	NPC* royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(300, 0, 60);

	list<Entity*>* entities = new list<Entity*>();
	entities->push_back(royd1);

	_stages.push(make_pair(0, entities));

	entities = new list<Entity*>();
	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(300 + SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	_stages.push(make_pair(300, entities));

	entities = new list<Entity*>();
	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(600 + SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(300 + SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	_stages.push(make_pair(600, entities));

	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(980 + SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(980 + SCREEN_WIDTH, 0, 10);
	entities->push_back(royd1);

	entities = new list<Entity*>();
	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(600 + SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	_stages.push(make_pair(980, entities));

	entities = new list<Entity*>();
	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(1000 + SCREEN_WIDTH, 0, 10);
	entities->push_back(royd1);

	_stages.push(make_pair(1000, entities));

	entities = new list<Entity*>();
	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(1300 + SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(1300 + SCREEN_WIDTH, 0, 10);
	entities->push_back(royd1);

	royd1 = entityFactory->GetObject<NPC>(EntityFactory::ROYD);
	royd1->Position = iPoint3(1000 + SCREEN_WIDTH, 0, 100);
	entities->push_back(royd1);

	_stages.push(make_pair(1300, entities));
}

bool FirstScene::can_advance()
{
	SDL_Rect* camera = &App->renderer->camera;
	int camera_pos = camera->x / SCREEN_SIZE;

	return _stages.empty() || abs(camera_pos) <= _stages.front().first * float(enemies_defeated) / float(_enemies.size());
}
