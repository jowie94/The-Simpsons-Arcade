#include <math.h>
#include "ModuleParticles.h"
#include "Engine.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{
}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");

	return true;
}

update_status ModuleParticles::PreUpdate()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		if ((*it)->to_delete == true)
		{
			if ((*it)->collider)
				(*it)->collider->to_delete = true;
			RELEASE(*it);
			it = active.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}

SDL_Texture* ModuleParticles::GetGraphics() const
{
	return graphics;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;

		if(p->Update() == false)
		{
			if ((*it)->collider)
				(*it)->collider->to_delete = true;
			RELEASE(*it);
			it = active.erase(it);
		}
		else 
		{
			// TODO: Draw particles with z index
			App->renderer->BlitBackground(graphics, int(p->x), int(p->y), &p->animation.GetCurrentFrame());
			++it;
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider* collider)
{
	Particle* clone = new Particle(particle);
	clone->x = float(x);
	clone->y = float(y);
	clone->initial_tick = SDL_GetTicks();
	clone->collider = collider;

	App->audio->PlayFx(clone->fx_id);

	active.push_back(clone);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{}

Particle::Particle(const Particle& p)
{
	this->animation = p.animation;
	this->animation.Reset();
	//this->collider = p.collider;
	this->speed = p.speed;
	this->x = p.x;
	this->y = p.y;
	this->life_time = p.life_time;
	this->fx_id = p.fx_id;
	this->speed = p.speed;
	this->to_delete = p.to_delete;
}

Particle::~Particle()
{
}

bool Particle::Update()
{
	//bool ret = x <= SCREEN_WIDTH && y <= SCREEN_HEIGHT;
	bool ret = collider ? !collider->to_delete : true;

	x += speed;
	if (collider)
		collider->rect.Position.x = int(x);
	to_delete = life_time >= 0 && SDL_GetTicks() >= life_time + initial_tick;
	// Return false if the particle must be destroyed

	return ret;
}

