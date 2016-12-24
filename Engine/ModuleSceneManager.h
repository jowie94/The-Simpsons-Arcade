#ifndef __MODULESCENEMANAGER_H__
#define __MODULESCENEMANAGER_H__

#include "Module.h"
class ModuleSceneManager :
	public Module
{
public:
	ModuleSceneManager();
	~ModuleSceneManager();


	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

private:
	// Scene* _currentScene;

};

#endif // __MODULESCENEMANAGER_H__
