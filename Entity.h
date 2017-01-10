#ifndef __Entity_H__
#define __Entity_H__

#include "Point.h"
#include "Globals.h"

struct SDL_Texture;
struct Collider;

class Entity
{
public:
	enum EntityType
	{
		PLAYER,
		ENEMY,
		UNKNOWN
	};
	Entity();
	Entity(EntityType entityType);
	virtual ~Entity();
	virtual bool Start();
	virtual update_status Update();
	virtual bool CleanUp();
	bool isCreature() const;
public:
	SDL_Texture* graphics = nullptr;
	EntityType entityType = UNKNOWN;
	iPoint initPos;
	iPoint position;
	Collider* baseCollider = nullptr;
};

#endif // __Entity_H__