#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

struct Particle
{
	bool to_delete = false;

	// TODO 1: Fill in the structure with all the properties you need for each particle
	Animation particle_anim;
	unsigned int fx;
	iPoint position;
	iPoint speed;
	bool fx_played;
	Uint32 born;
	Uint32 time;

	// TODO 11: Add an optional collider to each particle
	Collider* particle_collider;

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
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y,Uint32 delay,COLLIDER_TYPE type = COLLIDER_NONE); // feel free to expand this call
	void OnCollision(Collider* c1, Collider* c2);

private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> active;

public:

	// prototype particles go here ...
	Particle fire1;
	Particle fire2;
	Particle shuriken;
};

#endif // __MODULEPARTICLES_H__