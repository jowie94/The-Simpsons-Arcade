#include "Globals.h"
#include "Engine.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

bool ShouldColide[6][6] =
{
	{ false, false, true, true, true, false },
	{ false, false, true, true, true, false },
	{ true, true, false, false, true, false },
	{ true, true, false, false, false, false },
	{ true, true, true, false, false, false },
	{ false, false, false, false, false, false }
};

ModuleCollision::ModuleCollision()
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		Collider* col = *it;
		for (list<Collider*>::iterator it2 = ++it; it2 != colliders.end(); ++it2)
		{
			Collider* other = *it2;
			if (ShouldColide[col->type][other->type] && col->CheckCollision(other->rect))
			{
				if (col->notify_to)
					col->notify_to->Notify(col, other);
				if (other->notify_to)
					other->notify_to->Notify(other, col);
			}
		}
	}
	// After making it work, review that you are doing the minumum checks possible


	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect)
{
	Collider* ret = new Collider(rect);

	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// Return true if the argument and the own rectangle are intersecting
	return !(rect.x > r.x + r.w || r.x > rect.x + rect.w || rect.y > r.y + r.h ||  r.y > rect.y + rect.h);
}
