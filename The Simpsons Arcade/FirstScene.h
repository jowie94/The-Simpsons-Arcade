#ifndef __FIRSTSCENE_H__
#define __FIRSTSCENE_H__

#include "Scene.h"

struct SDL_Texture;

class FirstScene :
	public Scene
{
public:
	FirstScene(bool active);
	~FirstScene();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	SDL_Texture* _background;
	SDL_Rect _floor, _walls;

};

#endif // __FIRSTSCENE_H__
