#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

#include "Scene.h"
#include "ModuleFonts.h"

class WinScene :
	public Scene
{
public:
	WinScene(bool active);
	~WinScene();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	ModuleFonts::Font* _font;

};

#endif // __WIN_SCENE_H__
