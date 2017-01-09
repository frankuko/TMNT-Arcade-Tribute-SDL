#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "PlayerStateMachine.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Collider* collider = nullptr;
	Animation idle;
	Animation up;
	Animation down;
	Animation upright;
	Animation right;

	//State Machine for the player
	PlayerStateMachine stateMachine;

	// Animations 
	Animation kick;
	Animation throwWeapon;
	Animation attack1;
	Animation attack2;
	Animation attack3;
	Animation attack4;

	Animation jump;
	Animation jumpAttack1;
	Animation jumpAttack2;
	Animation jumpAttack3;
	
	Animation hit1;
	Animation hit2;
	Animation hit3;
	Animation hitBehind1;
	Animation hitBehind2;
	Animation hitBehind3;


	iPoint position;
	bool destroyed = false;
	void OnCollision(Collider* c1, Collider* c2);
};

#endif