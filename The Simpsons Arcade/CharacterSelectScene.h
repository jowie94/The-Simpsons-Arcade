#pragma once
#include "Scene.h"
class CharacterSelectScene :
	public Scene
{
public:
	CharacterSelectScene(bool active);
	~CharacterSelectScene();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	SDL_Texture* _graphics;

	std::vector<SDL_Rect*> _rects;
	std::vector<SDL_Rect*> _labels;
	
	int rectHSize = 72;
	int rectVSize = 160;

	int labelHSize = 72;
	int labelVSize = 28;
};

