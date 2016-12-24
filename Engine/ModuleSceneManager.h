#ifndef __MODULESCENEMANAGER_H__
#define __MODULESCENEMANAGER_H__

#include "Module.h"
class Scene;

class ModuleSceneManager :
	public Module
{
public:
	ModuleSceneManager();
	~ModuleSceneManager();

	void SetInitialScene(Scene* initial);
	void SetScene(Scene* scene);

	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

private:
	Scene* _currentScene = nullptr;

};

#endif // __MODULESCENEMANAGER_H__
