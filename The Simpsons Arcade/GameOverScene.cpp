#include "GameOverScene.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleSceneManager.h"
#include "FirstScene.h"

GameOverScene::GameOverScene(bool active) : Scene(active)
{
}

GameOverScene::~GameOverScene()
{
}

bool GameOverScene::Start()
{
	App->audio->PlayMusic("Simpsons/audio/43-game-over.ogg", 0.f, 0);
	_font = App->fonts->Load("Simpsons/font.png", "abcdefghijklmnopqrstuvwxyz0123456789.,'''?!@_#$%&()+-/: ");
	return true;
}

update_status GameOverScene::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->scene_manager->SetScene(new FirstScene(false));
	else
	{
		App->fonts->Write("game over!", 100, 100, _font);
		App->fonts->Write("press space to try again", 50, 200, _font);
	}

	return UPDATE_CONTINUE;
}

bool GameOverScene::CleanUp()
{
	return true;
}
