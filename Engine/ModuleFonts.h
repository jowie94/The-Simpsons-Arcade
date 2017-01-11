#ifndef __MODULE_FONTS_H__
#define __MODULE_FONTS_H__

#include "Module.h"
#include <SDL/include/SDL.h>
#include <list>

class ModuleFonts :
	public Module
{
public:
	struct Font
	{
		SDL_Texture* FontTexture;
		const char* Mask;
	};


	ModuleFonts();
	~ModuleFonts();

	update_status Update() override;
	bool CleanUp() override;

	Font* Load(const char* path, const char* mask);
	void Unload(Font* font);
	void Write(const std::string& str, int x, int y, Font* font) const;

private:
	std::list<Font*> _fonts;


	static int find(char c, const char* mask);
};

#endif // __MODULE_FONTS_H__
