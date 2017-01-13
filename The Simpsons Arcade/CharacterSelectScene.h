#pragma once
#include "Scene.h"
class CharacterSelectScene :
	public Scene
{
public:
	CharacterSelectScene(bool active);
	~CharacterSelectScene();

	bool Start() override;
	bool CleanUp() override;

private:
	SDL_Texture* _graphics;
};

