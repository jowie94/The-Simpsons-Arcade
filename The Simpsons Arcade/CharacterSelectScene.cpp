#include "CharacterSelectScene.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "FirstScene.h"
#include "ModuleSceneManager.h"
#include "Player.h"

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
		_rects.push_back(new SDL_Rect({ i*_rectHSize, 0, _rectHSize, _rectVSize }));
		_labels.push_back(new SDL_Rect({ i*_labelHSize, 356, _labelHSize, _labelVSize }));
		_bubbles.push_back(new SDL_Rect({ i * 32, 672, 32, 28 }));
	}

	return true;
}

update_status CharacterSelectScene::Update()
{
	for (int i = 0; i < 4; ++i)
	{
		App->renderer->DirectBlit(_graphics, _rectHSize*i, 0, _rects[i]);
		App->renderer->DirectBlit(_graphics, _rectHSize*i, _rectVSize - _labelVSize - 4, _labels[i]);
	}

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
	App->textures->Unload(_graphics);

	for (int i = 0; i < 4; ++i)
	{
		RELEASE(_rects[i]);
		RELEASE(_labels[i]);
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
