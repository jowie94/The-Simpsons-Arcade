#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct Collider;
struct SDL_Texture;

struct Particle
{
	bool to_delete = false;

	Animation animation;
	Collider* collider = nullptr;
	float speed;
	int life_time;
	float x, y;
	int fx_id;
	Uint32 initial_tick;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	SDL_Texture* GetGraphics() const;
	void AddParticle(const Particle& particle, int x, int y, Collider* collider = nullptr);

private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> active;

public:

	// prototype particles go here ...
};

#endif // __MODULEPARTICLES_H__