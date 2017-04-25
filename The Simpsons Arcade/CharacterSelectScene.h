#pragma once
#include "Scene.h"

class PlayerSelectorBox;

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
	int firstFreePosition(int pos = 0, int direction = 1) const;

	SDL_Texture* _graphics;

	std::vector<PlayerSelectorBox*> _boxes;
	std::vector<SDL_Rect*> _bubbles;

	int _positions[4] = { -1, -1, -1, -1 };
	bool _selected[4] = { false, false, false, false };
	
	int _rectHSize = 72;
	int _rectVSize = 160;

	int _labelHSize = 72;
	int _labelVSize = 28;
};

