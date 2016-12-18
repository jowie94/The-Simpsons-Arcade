#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

#include "SDL/include/SDL.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleParticles;

// Game modules ---

class Engine
{
public:

	enum State
	{
		CREATION,
		START,
		UPDATE,
		FINISH,
		EXIT
	};

	Engine();
	~Engine();

	int Loop();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleCollision* collision;
	ModuleParticles* particles;

	// Game modules ---

private:
	State state;

	std::list<Module*> modules;
};

extern Engine* App;

#endif // __APPLICATION_CPP__