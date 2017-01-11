#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "Scene.h"
#include "ModuleFonts.h"

class GameOverScene :
	public Scene
{
public:
	GameOverScene(bool active);
	~GameOverScene();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	ModuleFonts::Font* _font;

};

#endif // __GAMEOVER_SCENE_H__
