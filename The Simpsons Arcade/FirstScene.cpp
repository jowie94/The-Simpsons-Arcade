#include "FirstScene.h"
#include "Engine.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "EntityFactory.h"
#include "Player.h"
#include "ModuleSceneManager.h"

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

	Player* homer = App->scene_manager->GetEntityFactory()->GetObject<Player>(EntityFactory::HOMER);
	homer->Position.x = 70;
	homer->Position.z = 50;
	AddPlayer(homer);

	NPC* royd1 = App->scene_manager->GetEntityFactory()->GetObject<NPC>(EntityFactory::ROYD);
	AddEnemy(royd1);
	royd1->Position = iPoint3(200, 0, 60);

	return Scene::Start();
}

update_status FirstScene::Update()
{
	// Draw everything --------------------------------------
	App->renderer->BlitBackground(_background, 0, 0, &_walls);
	App->renderer->BlitBackground(_background, 0, 0, &_floor);

	iPoint3 min(xmax, 0, zmax), max(0, 0, 0);

	for (Entity* entity : _players)
	{
		iPoint3 pos = entity->Position;

		max.x = MAX(pos.x, max.x);
		max.z = MAX(pos.z, max.z);
		min.x = MIN(pos.x, min.x);
		min.z = MIN(pos.z, min.z);
	}

	iPoint3 mid = (min + max) / 2;
	SDL_Rect* camera = &App->renderer->camera;

	int y = ZTOY(mid.z, App->renderer->RenderingAngle);
	camera->y = (y - _walls.h + SCREEN_HEIGHT - 20) * SCREEN_SIZE;

	camera->y = CLAMP(camera->y, (-_walls.h + SCREEN_HEIGHT) * SCREEN_SIZE, 0);

	int right_bound = -(camera->x) / SCREEN_SIZE + SCREEN_WIDTH - 150;
	if (mid.x >= right_bound)
		camera->x -= 2 * SCREEN_SIZE;

	camera->x = CLAMP(camera->x, (-_walls.w + SCREEN_WIDTH) * SCREEN_SIZE, 0);

	xmin = -camera->x / SCREEN_SIZE + 16;
	xmax = -camera->x / SCREEN_SIZE + SCREEN_WIDTH - 50;
	return Scene::Update();
}

bool FirstScene::CleanUp()
{
	App->textures->Unload(_background);

	return Scene::CleanUp();
}
