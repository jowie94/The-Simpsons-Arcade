#ifndef __MODULESCENEMANAGER_H__
#define __MODULESCENEMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "BaseFactory.h"
class Scene;

class ModuleSceneManager :
	public Module
{
public:
	ModuleSceneManager();
	~ModuleSceneManager();

	void SetInitialScene(Scene* initial);
	void SetScene(Scene* scene);
	const Scene* CurrentScene() const;
	void SetEntityFactory(BaseFactory<Entity>* factory);
	BaseFactory<Entity>* GetEntityFactory() const;

	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

private:
	Scene* _currentScene = nullptr;
	BaseFactory<Entity>* entity_factory = nullptr;

};

#endif // __MODULESCENEMANAGER_H__
