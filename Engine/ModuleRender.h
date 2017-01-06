#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include <queue>
#include <ios>
#include "Rectangle3.h"
#include <functional>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	struct RenderData
	{
		bool flip;
		SDL_Texture* texture;
		SDL_Rect* section;
		SDL_Rect* rect;
	};

	struct QuadData
	{
		SDL_Rect* rect;
		SDL_Color* color;
	};

	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool BlitBackground(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f);
	bool AbsoluteBlit(SDL_Texture* texture, int x, int y, int z, SDL_Rect* section, float speed = 1.0f, bool flip = false);
	bool Blit(SDL_Texture* texture, int x, int y, int z, SDL_Rect* section, float speed = 1.0f, bool flip = false);
	bool AbsoluteDrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);
	bool AbsoluteDrawQuad(const iRectangle3& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);
	bool DrawQuad(const iRectangle3& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;

	int RenderingAngle = 0;
	
private:
	std::queue<RenderData*> _background;
	typedef std::pair<int, RenderData*> PIRD;
	std::priority_queue<PIRD, std::vector<PIRD>, std::greater<PIRD>> _foreground;
	std::queue<QuadData*> _quads;

	int _background_height = 0;
};

#endif // __MODULERENDER_H__
