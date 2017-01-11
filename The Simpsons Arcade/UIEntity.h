#ifndef __UIENTITY_H__
#define __UIENTITY_H__

#include "Entity.h"
#include "ModuleFonts.h"

class UIEntity :
	public Entity
{
public:
	UIEntity();
	~UIEntity();

	bool Start() override;
	void Update() override;
	bool CleanUp() override;

private:
	SDL_Texture* _graphics;
	std::vector<SDL_Rect*> _rects;
	std::vector<SDL_Rect*> _lifes;
	ModuleFonts::Font* _font;
};

#endif // __UIENTITY_H__
