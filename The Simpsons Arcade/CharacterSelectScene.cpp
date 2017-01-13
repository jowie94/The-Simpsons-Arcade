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
	_graphics = App->textures->Load("Simpsons/player_selection.png");
	return true;
}

bool CharacterSelectScene::CleanUp()
{
	App->textures->Unload(_graphics);
	return true;
}
