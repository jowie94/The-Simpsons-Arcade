#include "WinScene.h"
#include "ModuleInput.h"
#include "FirstScene.h"
#include "ModuleAudio.h"
#include "ModuleSceneManager.h"

WinScene::WinScene(bool active) : Scene(active)
{
}

WinScene::~WinScene()
{
}

bool WinScene::Start()
{
	App->audio->PlayMusic("Simpsons/audio/139-Ending & Credits.ogg", 0.f, 0);
	_font = App->fonts->Load("Simpsons/font.png", "abcdefghijklmnopqrstuvwxyz0123456789.,'''?!@_#$%&()+-/: ");
	return true;
}

update_status WinScene::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->scene_manager->SetScene(new FirstScene(false));
	else
	{
		App->fonts->Write("you won!", 110, 100, _font);
		App->fonts->Write("press space to play again", 42, 200, _font);
	}

	return UPDATE_CONTINUE;
}

bool WinScene::CleanUp()
{
	return true;
}
