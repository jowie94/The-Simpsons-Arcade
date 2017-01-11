#ifndef __MODULE_TIMER_H__
#define __MODULE_TIMER_H__

#include "Module.h"

class ModuleTimer :
	public Module
{
public:
	struct Timer
	{
		bool finished = false;
	};

	ModuleTimer();
	~ModuleTimer();

	bool Init() override;

	Timer* AddTimer(uint interval);
};

#endif // __MODULE_TIMER_H__
