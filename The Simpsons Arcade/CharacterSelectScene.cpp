#include "CharacterSelectScene.h"
#include "ModuleTextures.h"

CharacterSelectScene::CharacterSelectScene(bool active) : Scene(active)
{
}

CharacterSelectScene::~CharacterSelectScene()
{
}

bool CharacterSelectScene::Start()
{
	_graphics = App->textures->Load("Simpsons/player_selector.png");

	for (int i = 0; i < 4; ++i)
	{
		_rects.push_back(new SDL_Rect({ i*rectHSize, 0, rectHSize, rectVSize }));
		_labels.push_back(new SDL_Rect({ i*labelHSize, 356, labelHSize, labelVSize }));
	}

	for (int i = 0; i < 4; ++i)
	{
		
	}

	return true;
}

update_status CharacterSelectScene::Update()
{
	for (int i = 0; i < 4; ++i)
	{
		App->renderer->DirectBlit(_graphics, rectHSize*i, 0, _rects[i]);
		App->renderer->DirectBlit(_graphics, rectHSize*i, rectVSize - labelVSize - 4, _labels[i]);
	}

	return UPDATE_CONTINUE;
}

bool CharacterSelectScene::CleanUp()
{
	App->textures->Unload(_graphics);
	return true;
}
