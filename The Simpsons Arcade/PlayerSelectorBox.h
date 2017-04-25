#pragma once
#include "Entity.h"
#include "Point.h"

class PlayerSelectorBox
	: public Entity
{
public:
	PlayerSelectorBox();
	~PlayerSelectorBox();

	void Update() override;

	void SetGraphics(SDL_Texture* graphics);
	void SetCoords(int frameNum, const iPoint& headCoords, const iPoint& headSize, const iPoint& eyeCoords, const iPoint& eyeOpenCoords);
	void Activate();

private:

	SDL_Texture* _graphics = nullptr;

	bool _active = false;
	int _frameNum = 0;
	iPoint _headCoords;
	iPoint _headSize;
	iPoint _eyeCoords;
	iPoint _eyeOpenCoords;
};

