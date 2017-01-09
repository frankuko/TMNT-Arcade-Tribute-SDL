#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"

// TODO 9: Create a matrix of game specific types of collision for early discard
// Example: lasers should not collide with lasers but should collider with walls
// enemy shots will collide with other enemies ? and against walls ?
enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_ENEMY_WEAPON,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	// TODO 10: Add a way to notify other classes that a collision happened
	Module* callback;
	COLLIDER_TYPE type;
	

	Collider(SDL_Rect rectangle,COLLIDER_TYPE type, Module* callback = nullptr) : // expand this call if you need to
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect,COLLIDER_TYPE type, Module* callback = nullptr);
	Collider* RemoveCollider(Collider* collider);
	void DebugDraw();

private:

	std::list<Collider*> colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__