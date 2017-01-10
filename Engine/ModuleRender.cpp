#include "Globals.h"
#include "Engine.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// debug camera
	int speed = 1;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->renderer->camera.y += speed;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->renderer->camera.y -= speed;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->renderer->camera.x += speed;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->renderer->camera.x -= speed;

	bool ret = true;

	while (!_background.empty() && ret)
	{
		RenderData* data = _background.front();
		if (SDL_RenderCopy(renderer, data->texture, data->section, data->rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}

		RELEASE(data->rect);
		RELEASE(data);
		_background.pop();
	}

	while (!_foreground.empty() && ret)
	{
		RenderData* data = _foreground.top().second;

		SDL_RendererFlip flags = data->flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		SDL_Point center = { 0, 0 };
		if (SDL_RenderCopyEx(renderer, data->texture, data->section, data->rect, 0, &center, flags) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}

		RELEASE(data->rect);
		RELEASE(data);
		_foreground.pop();
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	while (!_quads.empty() && ret)
	{
		QuadData* data = _quads.front();
		SDL_SetRenderDrawColor(renderer, data->color->r, data->color->g, data->color->b, data->color->a);

		if (SDL_RenderFillRect(renderer, data->rect) != 0)
		{
			LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
			ret = false;
		}

		RELEASE(data->rect);
		RELEASE(data->color);
		RELEASE(data);
		_quads.pop();
	}

	return ret ? UPDATE_CONTINUE : UPDATE_ERROR;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	while (!_background.empty())
	{
		RenderData* data = _background.front();
		RELEASE(data->rect);
		RELEASE(data);
		_background.pop();
	}

	while (!_foreground.empty())
	{
		RenderData* data = _foreground.top().second;
		RELEASE(data->rect);
		RELEASE(data);
		_foreground.pop();
	}

	while (!_quads.empty())
	{
		QuadData* data = _quads.front();
		RELEASE(data->rect);
		RELEASE(data->color);
		RELEASE(data);
		_quads.pop();
	}

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::BlitBackground(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed)
{
	bool ret = true;
	SDL_Rect* rect = new SDL_Rect;
	rect->x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect->y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if(section != NULL)
	{
		rect->w = section->w;
		rect->h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
	}

	if (rect->w > _background_height)
		_background_height = rect->h;

	rect->w *= SCREEN_SIZE;
	rect->h *= SCREEN_SIZE;

	_background.push(new RenderData({ false, texture, section, rect }));

	return ret;
}

bool ModuleRender::AbsoluteBlit(SDL_Texture* texture, int x, int y, int z, SDL_Rect* section, float speed, bool flip)
{
	bool ret = true;
	SDL_Rect* rect = new SDL_Rect;
	rect->x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	y += ZTOY(z, RenderingAngle);
	rect->y = (int)(camera.y * speed) + y * SCREEN_SIZE; // TODO: Add z to y

	if (section != NULL)
	{
		rect->w = section->w;
		rect->h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
	}

	rect->w *= SCREEN_SIZE;
	rect->h *= SCREEN_SIZE;

	_foreground.emplace(z, new RenderData({ flip, texture, section, rect }));

	return ret;
}

bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, int z, SDL_Rect* section, float speed, bool flip)
{
	if (_background_height)
		y = _background_height - y;
	z *= -1;

	return AbsoluteBlit(texture, x, y, z, section, speed, flip);
}

bool ModuleRender::AbsoluteDrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_Color* color = new SDL_Color({ r,g,b,a });
	
	SDL_Rect* rec = new SDL_Rect(rect);
	if (use_camera)
	{
		rec->x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec->y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec->w *= SCREEN_SIZE;
		rec->h *= SCREEN_SIZE;
	}

	_quads.emplace(new QuadData({ rec, color }));

	return ret;
}

bool ModuleRender::AbsoluteDrawQuad(const iRectangle3& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	int y = rect.Position.y + ZTOY(rect.Position.z, RenderingAngle);
	return AbsoluteDrawQuad({ rect.Position.x, y, rect.w, rect.h }, r, g, b, a, use_camera);
}

bool ModuleRender::DrawQuad(const iRectangle3& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	iRectangle3 rec = rect;
	if (_background_height)
		rec.Position.y = _background_height - rect.Position.y;
	rec.Position.z *= -1;

	return AbsoluteDrawQuad(rec, r, g, b, a, use_camera);
}

