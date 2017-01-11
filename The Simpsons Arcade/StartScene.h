#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "Scene.h"

class StartScene :
	public Scene
{
public:
	StartScene(bool active);
	~StartScene();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	SDL_Texture* _graphics;
};

#endif // __START_SCENE_H__
