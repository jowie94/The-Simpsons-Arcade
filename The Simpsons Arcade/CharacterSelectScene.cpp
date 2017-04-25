#include "CharacterSelectScene.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "FirstScene.h"
#include "ModuleSceneManager.h"
#include "Player.h"
#include "PlayerSelectorBox.h"

CharacterSelectScene::CharacterSelectScene(bool active) : Scene(active)
{
}

CharacterSelectScene::~CharacterSelectScene()
{
}

bool CharacterSelectScene::Start()
{
	_graphics = App->textures->Load("Simpsons/player_selector.png");

	for (int i = 0; i < 4; ++i)
	{
		_bubbles.push_back(new SDL_Rect({ i * 32, 672, 32, 28 }));
	}

	static iPoint headCoords[4] = {};
	static iPoint headSizes[4] = {};
	static iPoint eyeCoords[4] = {};
	static iPoint eyeOpenCoords[4] = {};

	// TODO: Use factory
	for (int i = 0; i < 4; ++i)
	{
		PlayerSelectorBox* box = new PlayerSelectorBox;
		AddEntity(box);
		box->SetGraphics(_graphics);
		box->SetCoords(i, headCoords[i], headSizes[i], eyeCoords[i], eyeOpenCoords[i]);
		_boxes.push_back(box);
	}

	return true;
}

update_status CharacterSelectScene::Update()
{
	Scene::Update();

	int positioned = 0, selected = 0;
	
	for (int i = 0; i < 4; ++i)
	{
		if (_positions[i] != -1)
		{
			int axis = 0;
			axis -= App->input->GetPlayerKey(i, LEFT) == KEY_DOWN ? 1 : 0;
			axis += App->input->GetPlayerKey(i, RIGHT) == KEY_DOWN ? 1 : 0;

			if (!_selected[i])
			{
				if (axis)
				{
					int pos = _positions[i];
					_positions[i] = -1;

					pos = (pos + axis) % 4;
					pos = pos < 0 ? 3 : pos;
					_positions[i] = firstFreePosition(pos, axis);
				}
				else if (App->input->GetPlayerKey(i, ATTACK) == KEY_DOWN)
				{
					_boxes[i]->Activate();
					_selected[i] = true;
				}
			}

			App->renderer->DirectBlit(_graphics, _rectHSize * _positions[i] + 20, _rectVSize - _labelVSize - 20, _bubbles[i]);
			++positioned;
		}
		else if (App->input->GetPlayerKey(i, ATTACK) == KEY_DOWN)
		{
			_positions[i] = firstFreePosition();
		}

		if (_selected[i])
		{
			App->renderer->DirectBlit(_graphics, _rectHSize * _positions[i] + 20, _rectVSize - _labelVSize - 20, _bubbles[i]);
			++selected;
		}
	}

	if (positioned > 0 && positioned == selected)
	{
		FirstScene* scene = new FirstScene(false);
		
		for (int i = 0; i < 4; ++i)
		{
			if (_selected[i])
			{
				Player* player = App->scene_manager->GetEntityFactory()->GetObject<Player>(_positions[i]);
				player->ControllerNumber = i;
				scene->AddPlayer(player);
			}
		}

		App->scene_manager->SetScene(scene);
	}

	return UPDATE_CONTINUE;
}

bool CharacterSelectScene::CleanUp()
{
	Scene::CleanUp();

	App->textures->Unload(_graphics);

	for (int i = 0; i < 4; ++i)
	{
		RELEASE(_bubbles[i]);
	}

	return true;
}

int CharacterSelectScene::firstFreePosition(int pos, int direction) const
{
	bool free_positions[4];
	memset(free_positions, true, 4);
	for (int i = 0; i < 4; ++i)
	{
		if (_positions[i] != -1)
			free_positions[_positions[i]] = false;
	}

	while (!free_positions[pos])
	{
		pos = (pos + direction) % 4;
		pos = pos < 0 ? 3 : pos;
	}

	return pos;
}
