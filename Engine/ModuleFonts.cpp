#include "ModuleFonts.h"
#include "Engine.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModuleFonts::ModuleFonts()
{
}

ModuleFonts::~ModuleFonts()
{
}

update_status ModuleFonts::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleFonts::CleanUp()
{
	for (Font* font : _fonts)
	{
		App->textures->Unload(font->FontTexture);
		RELEASE(font);
	}

	_fonts.clear();

	return true;
}

ModuleFonts::Font* ModuleFonts::Load(const char* path, const char* mask)
{
	Font* font = new Font;
	font->FontTexture = App->textures->Load(path);
	font->Mask = mask;

	_fonts.push_back(font);

	return font;
}

void ModuleFonts::Unload(Font* font)
{
	_fonts.remove(font);
	App->textures->Unload(font->FontTexture);
	RELEASE(font->Mask);
	RELEASE(font);
}

void ModuleFonts::Write(const std::string& str, int x, int y, Font* font) const
{
	for (char c : str)
	{
		int index = find(c, font->Mask);
		SDL_Rect section = { 8 * index, 0, 8, 9 };
		App->renderer->DirectBlit(font->FontTexture, x, y, &section);
		x += 8;
	}
}

int ModuleFonts::find(char c, const char* mask)
{
	const char* pos = mask;
	while (pos)
	{
		if (*pos == c)
			return pos - mask;
		++pos;
	}
}
