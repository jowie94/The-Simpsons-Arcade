#include "StartScene.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleSceneManager.h"
#include "CharacterSelectScene.h"

StartScene::StartScene(bool active) : Scene(active)
{
}

StartScene::~StartScene()
{
}

bool StartScene::Start()
{
	_graphics = App->textures->Load("Simpsons/play_screen.png");
	App->audio->PlayMusic("Simpsons/audio/01-simpsons-theme-song.ogg");
	return true;
}

update_status StartScene::Update()
{
	App->renderer->DirectBlit(_graphics, 0, 0, nullptr);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		App->scene_manager->SetScene(new CharacterSelectScene(false));

	return UPDATE_CONTINUE;
}

bool StartScene::CleanUp()
{
	App->textures->Unload(_graphics);
	return true;
}
