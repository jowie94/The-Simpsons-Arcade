#include "FirstScene.h"
#include "Engine.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"


FirstScene::FirstScene(bool active) : Scene(active)
{
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

	return true;
}

update_status FirstScene::Update()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(_background, 0, 0, &_walls);
	App->renderer->Blit(_background, 0, 0, &_floor);

	return Scene::Update();
}

bool FirstScene::CleanUp()
{
	App->textures->Unload(_background);

	return Scene::CleanUp();
}
