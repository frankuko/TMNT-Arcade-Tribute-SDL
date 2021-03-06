#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_WEAPON] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_WEAPON] = true;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_WEAPON] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_WEAPON] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_FEET] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_WEAPON] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_WEAPON] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;

	matrix[COLLIDER_ENEMY_WEAPON][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_WEAPON][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_WEAPON][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_WEAPON][COLLIDER_PLAYER_WEAPON] = false;
	matrix[COLLIDER_ENEMY_WEAPON][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_WEAPON][COLLIDER_ENEMY_WEAPON] = false;

	matrix[COLLIDER_PLAYER_WEAPON][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_WEAPON][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_WEAPON][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_WEAPON][COLLIDER_PLAYER_WEAPON] = false;
	matrix[COLLIDER_PLAYER_WEAPON][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_WEAPON][COLLIDER_ENEMY_WEAPON] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_WEAPON] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_WEAPON] = false;

	matrix[COLLIDER_ENEMY_FEET][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_FEET][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_FEET][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_FEET][COLLIDER_PLAYER_WEAPON] = true;
	matrix[COLLIDER_ENEMY_FEET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_FEET][COLLIDER_ENEMY_WEAPON] = false;
	matrix[COLLIDER_ENEMY_FEET][COLLIDER_PLAYER_FEET] = false;

	matrix[COLLIDER_PLAYER_FEET][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_WEAPON] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_ENEMY_FEET] = false;
	matrix[COLLIDER_PLAYER_FEET][COLLIDER_PLAYER_FEET] = false;
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
	// TODO 8: Check collisions between all colliders. 
	// After making it work, review that you are doing the minumum checks possible


	list<Collider*>::iterator it = colliders.begin();

	Collider* c1;
	Collider* c2;

	while (it != colliders.end())
	{
		c1 = *it;

		list<Collider*>::iterator it2 = it++;

		while (it2 != colliders.end())
		{
			c2 = *it2;
			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}

			it2++;
		}
	}



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

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect,type,callback);

	colliders.push_back(ret);

	return ret;
}

Collider* ModuleCollision::RemoveCollider(Collider * collider)
{
	if (collider != nullptr)
	{
		colliders.remove(collider);
		RELEASE(collider);
	}


	return nullptr;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// TODO 7: Create by hand (avoid consulting the internet) a simple collision test
	// Return true if the argument and the own rectangle are intersecting
	return (rect.x < r.x + r.w && rect.x + rect.w > r.x &&
			rect.y < r.y + r.h && rect.y + rect.h > r.y);
}
