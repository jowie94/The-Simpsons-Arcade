#include "ModuleTimer.h"
#include <SDL/include/SDL.h>

Uint32 _internal_callback(Uint32 interval, void* param)
{
	static_cast<ModuleTimer::Timer*>(param)->finished = true;
	return 0;
}


ModuleTimer::ModuleTimer()
{
}

ModuleTimer::~ModuleTimer()
{
}

bool ModuleTimer::Init()
{
	bool ret = true;

	if (SDL_Init(SDL_INIT_TIMER) < 0)
	{
		LOG("SDL_Timer could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

ModuleTimer::Timer* ModuleTimer::AddTimer(uint interval)
{
	Timer* timer = new Timer;

	return SDL_AddTimer(interval, &_internal_callback, timer) ? timer : nullptr;
}