#include "Engine.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneManager.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleTimer.h"
#include "ModuleFonts.h"

using namespace std;

Engine* App;

Engine::Engine()
{
	state = State::CREATION;

	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());

	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(audio = new ModuleAudio());

	// Game Modules
	modules.push_back(scene_manager = new ModuleSceneManager());

	// Modules to draw on top of game logic
	modules.push_back(collision = new ModuleCollision());
	modules.push_back(particles = new ModuleParticles());
	modules.push_back(timer = new ModuleTimer());
	modules.push_back(fonts = new ModuleFonts());
	//modules.push_back(fade = new ModuleFadeToBlack());

	App = this;
}

Engine::~Engine()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

int Engine::Loop()
{
	int ret = EXIT_FAILURE;
	while (state != EXIT)
	{
		switch (state)
		{
		case CREATION:
			state = START;
			break;
		case START:

			LOG("Engine Init --------------");
			if (App->Init() == false)
			{
				LOG("Engine Init exits with error -----");
				state = EXIT;
			}
			else
			{
				state = UPDATE;
				LOG("Engine Update --------------");
			}

			break;

		case UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Engine Update exits with error -----");
				state = EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = FINISH;
		}
			break;

		case FINISH:

			LOG("Engine CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Engine CleanUp exits with error -----");
			}
			else
				ret = EXIT_SUCCESS;

			state = EXIT;

			break;
		}
	}

	return ret;
}

bool Engine::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not anabled

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	// Start the first scene --

	return ret;
}

update_status Engine::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->PostUpdate();

	return ret;
}

bool Engine::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if((*it)->IsEnabled() == true) 
			ret = (*it)->CleanUp();

	return ret;
}

