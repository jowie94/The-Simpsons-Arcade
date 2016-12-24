#include "ModuleSceneManager.h"
#include "Scene.h"
#include <cassert>


ModuleSceneManager::ModuleSceneManager()
{
}


ModuleSceneManager::~ModuleSceneManager()
{
}

void ModuleSceneManager::SetScene(Scene* scene)
{
	assert(scene != nullptr);

	if (_currentScene) 
	{
		RELEASE(_currentScene);
		_currentScene->Disable();
	}

	_currentScene = scene;
	_currentScene->Enable();
}

update_status ModuleSceneManager::PreUpdate()
{
	return _currentScene ? _currentScene->PreUpdate() : UPDATE_CONTINUE;
}

update_status ModuleSceneManager::Update()
{
	return _currentScene ? _currentScene->Update() : UPDATE_CONTINUE;
}

update_status ModuleSceneManager::PostUpdate()
{
	return _currentScene ? _currentScene->PostUpdate() : UPDATE_CONTINUE;
}

bool ModuleSceneManager::CleanUp()
{
	bool res = _currentScene ? _currentScene->CleanUp() : true;
	RELEASE(_currentScene);
	return res;
}
