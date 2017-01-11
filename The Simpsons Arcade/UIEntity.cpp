#include "UIEntity.h"
#include "ModuleTextures.h"
#include "ModuleSceneManager.h"
#include "Scene.h"
#include "Player.h"

UIEntity::UIEntity()
{
}

UIEntity::~UIEntity()
{
}

bool UIEntity::Start()
{
	int hSize = 72;
	int vSize = 28;

	for (int i = 0; i < 4; ++i)
	{
		_rects.push_back(new SDL_Rect({ i*hSize, 0, hSize, vSize }));
		_lifes.push_back(new SDL_Rect({ 0, 56, 32, 13 }));
	}

	_font = App->fonts->Load("Simpsons/font.png", "abcdefghijklmnopqrstuvwxyz0123456789.,'''?!@_#$%&()+-/: ");
	_graphics = App->textures->Load("Simpsons/ui.png");
	return _graphics != nullptr;
}

void UIEntity::Update()
{
	vector<Player*> playerInScene(4, nullptr);

	list<Entity*> players;
	App->scene_manager->CurrentScene()->PlayerList(players);

	for (Entity* player : players)
	{
		Player* p = static_cast<Player*>(player);
		playerInScene[p->PlayerNumber] = p;
	}

	int hSize = 72;
	int vSize = 28;
	int lifeH = 32;

	for (int i = 0; i < 4; ++i)
	{
		SDL_Rect* rect = _rects[i];

		if (playerInScene[i])
		{
			rect->y = 0;
			App->renderer->BlitUI(_graphics, hSize*i, 0, rect);
			_lifes[i]->w = float(lifeH) * (float(playerInScene[i]->GetLife()) / 10.f);
			App->renderer->BlitUI(_graphics, hSize*i + 24, 10, _lifes[i]);
			char life[1] = { '0' + playerInScene[i]->Lifes };
			App->fonts->Write(life, hSize*(i+1) - 10, 15, _font);
		}
		else
		{
			rect->y = vSize;
			App->renderer->BlitUI(_graphics, hSize*i, 0, rect);
		}
	}
}

bool UIEntity::CleanUp()
{
	for (SDL_Rect* rect : _rects)
		RELEASE(rect);
	_rects.clear();

	for (SDL_Rect* rect : _lifes)
		RELEASE(rect);
	_lifes.clear();

	App->textures->Unload(_graphics);
	_graphics = nullptr;

	return true;
}
