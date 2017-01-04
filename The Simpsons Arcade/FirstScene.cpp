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

	SDL_Color mask = { 86, 177, 222, 0 };

	_background = App->textures->Load("Simpsons/first_scene.png", &mask);
	_walls.x = _floor.x = _floor.y = 4;
	_walls.y = 264;
	_walls.w =_floor.w = 1663;
	_walls.h = _floor.h = 255;

	Player* homer = App->scene_manager->GetEntityFactory()->GetObject<Player>(EntityFactory::HOMER);
	AddPlayer(homer);

	return Scene::Start();
}

update_status FirstScene::Update()
{
	// Draw everything --------------------------------------
	App->renderer->BlitBackground(_background, -64 / SCREEN_SIZE, -64 / SCREEN_SIZE, &_walls);
	App->renderer->BlitBackground(_background, -64 / SCREEN_SIZE, -64 / SCREEN_SIZE, &_floor);

	return Scene::Update();
}

bool FirstScene::CleanUp()
{
	App->textures->Unload(_background);

	return Scene::CleanUp();
}
