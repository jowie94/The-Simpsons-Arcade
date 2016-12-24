#include "ModuleSceneManager.h"



ModuleSceneManager::ModuleSceneManager()
{
}


ModuleSceneManager::~ModuleSceneManager()
{
}

update_status ModuleSceneManager::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleSceneManager::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleSceneManager::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleSceneManager::CleanUp()
{
	return true;
}
