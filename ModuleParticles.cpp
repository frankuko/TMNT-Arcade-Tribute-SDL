#include <math.h>
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("TMNT/stage_animation.png");

	LOG("Loading particles");
	graphics = App->textures->Load("rtype/stagepart.png");

	//fire1 
	fire1.particle_anim.frames.push_back({ 17, 430, 304, 65 });
	fire1.particle_anim.frames.push_back({ 335, 430, 304, 65 });
	fire1.particle_anim.frames.push_back({ 17, 495, 304, 65 });
	fire1.particle_anim.frames.push_back({ 335, 495, 304, 65 });
	fire1.particle_anim.frames.push_back({ 17, 560, 304, 65 });
	fire1.particle_anim.frames.push_back({ 335, 560, 304, 65 });
	fire1.particle_anim.frames.push_back({ 710, 533, 304, 65 });
	fire1.particle_anim.frames.push_back({ 1029, 533, 304, 65 });
	fire1.particle_anim.loop = true;
	fire1.particle_anim.speed = 0.09f;

	//fire2
	fire2.particle_anim.frames.push_back({ 335, 560, 304, 65 });
	fire2.particle_anim.frames.push_back({ 17, 560, 304, 65 });
	fire2.particle_anim.frames.push_back({ 335, 495, 304, 65 });
	fire2.particle_anim.frames.push_back({ 17, 495, 304, 65 });
	fire2.particle_anim.frames.push_back({ 335, 430, 304, 65 });
	fire2.particle_anim.frames.push_back({ 17, 430, 304, 65 });
	fire2.particle_anim.loop = true;
	fire2.particle_anim.speed = 0.09f;

	//ninja attack
	shuriken.particle_anim.frames.push_back({ 131, 329, 12, 12 });
	shuriken.particle_anim.frames.push_back({ 155, 353, 12, 12 });
	shuriken.particle_anim.frames.push_back({ 180, 328, 12, 12 });
	shuriken.particle_anim.loop = true;
	shuriken.particle_anim.speed = 0.2f;



	return true;
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

// Update: draw background
update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;

		if(p->Update() == false)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->particle_anim.GetCurrentFrame()));
			if (p->fx_played == false) 
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}

			++it;
		}

	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay, COLLIDER_TYPE type)
{
	// TODO 4: Fill in a method to create an instance of a prototype particle
	Particle *p = new Particle(particle);
	p->born = SDL_GetTicks()+delay;
	p->position.x = x;
	p->position.y = y;
	// TODO 15: Add Collider to particle
	if (type != COLLIDER_NONE)
	{
		p->particle_collider = App->collision->AddCollider({ p->position.x,p->position.y,0,0 }, type, this);
	}

	active.push_back(p);

}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;

		if (p->particle_collider == c1)
		{
			//App->particles->AddParticle(App->particles->explosion, p->position.x, p->position.y, 0);

			delete p;
			active.erase(it);


			break;
		}
		else ++it;
	}

}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), fx_played(false), time(0), particle_collider(nullptr)
{
	position.x = 0;
	position.y = 0;

	speed.x = 0;
	speed.y = 0;
}

// TODO 3: Fill in a copy constructor
Particle::Particle(const Particle& p) : particle_anim(p.particle_anim), fx(p.fx), born(p.born), fx_played(p.fx_played),time(p.time),
particle_collider(p.particle_collider),position(p.position),speed(p.speed)
{}

Particle::~Particle()
{
}

bool Particle::Update()
{
	bool ret = true;
	particle_anim.Reset();
	// TODO 5: This is the core of the particle functionality.
	// Return false if the particle must be destroyed
	if (time > 0)
	{
		if ((SDL_GetTicks() - born) > time)
			ret = false;
	}
	else
	{
		if (particle_anim.Finished())
			ret = false;
	}

	position.x += speed.x;
	position.y += speed.y;


	if (particle_collider != nullptr)
	{
		SDL_Rect r = particle_anim.GetCurrentFrame();
		particle_collider->rect = { position.x,position.y,r.w,r.h };
	}

	return ret;
}

