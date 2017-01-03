#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Point.h"
#include <SDL/include/SDL.h>

struct Sprite
{
	SDL_Rect Rect;
	iPoint Pivot;
};

#endif // __SPRITE_H__
