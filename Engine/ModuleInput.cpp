#include "Globals.h"
#include "Engine.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(), mouse({0, 0}), mouse_motion({0,0})
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
	RELEASE_ARRAY(keyboard);
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called before the first frame
bool ModuleInput::Start()
{
	return true;
}

// Called each loop iteration
update_status ModuleInput::PreUpdate()
{
	static SDL_Event event;

	mouse_motion = {0, 0};
	memset(windowEvents, false, WE_COUNT * sizeof(bool));
	
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for(int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if(mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if(mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}

	while(SDL_PollEvent(&event) != 0)
	{
		switch(event.type)
		{
			case SDL_QUIT:
				windowEvents[WE_QUIT] = true;
			break;

			case SDL_WINDOWEVENT:
				switch(event.window.event)
				{
					//case SDL_WINDOWEVENT_LEAVE:
					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_FOCUS_LOST:
					windowEvents[WE_HIDE] = true;
					break;

					//case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_SHOWN:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_MAXIMIZED:
					case SDL_WINDOWEVENT_RESTORED:
					windowEvents[WE_SHOW] = true;
					break;
				}
			break;

			case SDL_MOUSEBUTTONDOWN:
				mouse_buttons[event.button.button - 1] = KEY_DOWN;
			break;

			case SDL_MOUSEBUTTONUP:
				mouse_buttons[event.button.button - 1] = KEY_UP;
			break;

			case SDL_MOUSEMOTION:
				mouse_motion.x = event.motion.xrel / SCREEN_SIZE;
				mouse_motion.y = event.motion.yrel / SCREEN_SIZE;
				mouse.x = event.motion.x / SCREEN_SIZE;
				mouse.y = event.motion.y / SCREEN_SIZE;
			break;
		}
	}

	if(GetWindowEvent(EventWindow::WE_QUIT) == true || GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		return UPDATE_STOP;

	memset(&_axis, 0, sizeof(_axis)); // Clear input vector

	if (keys[SDL_SCANCODE_A])
	{
		_axis[0][X] -= 1;
	}
	if (keys[SDL_SCANCODE_D])
	{
		_axis[0][X] += 1;
	}

	if (keys[SDL_SCANCODE_W])
	{
		_axis[0][Y] += 1;
	}
	if (keys[SDL_SCANCODE_S])
	{
		_axis[0][Y] -= 1;
	}

	if (keys[SDL_SCANCODE_F])
	{
		_axis[1][X] -= 1;
	}
	if (keys[SDL_SCANCODE_H])
	{
		_axis[1][X] += 1;
	}

	if (keys[SDL_SCANCODE_T])
	{
		_axis[1][Y] += 1;
	}
	if (keys[SDL_SCANCODE_G])
	{
		_axis[1][Y] -= 1;
	}

	if (keys[SDL_SCANCODE_J])
	{
		_axis[2][X] -= 1;
	}
	if (keys[SDL_SCANCODE_L])
	{
		_axis[2][X] += 1;
	}

	if (keys[SDL_SCANCODE_I])
	{
		_axis[2][Y] += 1;
	}
	if (keys[SDL_SCANCODE_K])
	{
		_axis[2][Y] -= 1;
	}

	if (keys[SDL_SCANCODE_LEFT])
	{
		_axis[3][X] -= 1;
	}
	if (keys[SDL_SCANCODE_RIGHT])
	{
		_axis[3][X] += 1;
	}

	if (keys[SDL_SCANCODE_UP])
	{
		_axis[3][Y] += 1;
	}
	if (keys[SDL_SCANCODE_DOWN])
	{
		_axis[3][Y] -= 1;
	}

	_keys[0][ATTACK] = keyboard[SDL_SCANCODE_Z];
	_keys[0][JUMP] = keyboard[SDL_SCANCODE_X];
	
	_keys[1][ATTACK] = keyboard[SDL_SCANCODE_V];
	_keys[1][JUMP] = keyboard[SDL_SCANCODE_B];

	_keys[2][ATTACK] = keyboard[SDL_SCANCODE_M];
	_keys[2][JUMP] = keyboard[SDL_SCANCODE_COMMA];

	_keys[3][ATTACK] = keyboard[SDL_SCANCODE_KP_0];
	_keys[4][JUMP] = keyboard[SDL_SCANCODE_KP_2];

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

// ---------
bool ModuleInput::GetWindowEvent(EventWindow ev) const
{
	return windowEvents[ev];
}

const iPoint& ModuleInput::GetMousePosition() const
{
	return mouse;
}

const iPoint& ModuleInput::GetMouseMotion() const
{
	return mouse_motion;
}