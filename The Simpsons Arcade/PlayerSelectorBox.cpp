#include "PlayerSelectorBox.h"



PlayerSelectorBox::PlayerSelectorBox()
{
}


PlayerSelectorBox::~PlayerSelectorBox()
{
}

void PlayerSelectorBox::Update()
{
	static int rectHSize = 72;
	static int rectVSize = 160;
	static int labelHSize = 72;
	static int labelVSize = 28;

	SDL_Rect rect = { _frameNum * rectHSize, _active * rectVSize, rectHSize, rectVSize };
	SDL_Rect label = { _frameNum * labelHSize, 356, labelHSize, labelVSize };

	App->renderer->DirectBlit(_graphics, rectHSize * _frameNum, 0, &rect);
	App->renderer->DirectBlit(_graphics, rectHSize * _frameNum, rectVSize - labelVSize - 4, &label);
}

void PlayerSelectorBox::SetGraphics(SDL_Texture* graphics)
{
	_graphics = graphics;
}

void PlayerSelectorBox::SetCoords(int frameNum, const iPoint& headCoords, const iPoint& headSize, const iPoint& eyeCoords, const iPoint& eyeOpenCoords)
{
	_frameNum = frameNum;
	_headCoords = headCoords;
	_headSize = headSize;
	_eyeCoords = eyeCoords;
	_eyeOpenCoords = eyeOpenCoords;
}

void PlayerSelectorBox::Activate()
{
	_active = true;
}
