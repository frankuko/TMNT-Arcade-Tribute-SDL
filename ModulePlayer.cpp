#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(bool active) : Module(active)
{

	/*// idle animation (just the ship)
	idle.frames.push_back({66, 1, 32, 14});


	// move upwards
	up.frames.push_back({100, 1, 32, 14});
	up.frames.push_back({132, 0, 32, 14});
	up.loop = false;
	up.speed = 0.1f;

	// Move down
	down.frames.push_back({33, 1, 32, 14});
	down.frames.push_back({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;*/


	// idle animation
	idle.frames.push_back({ 0, 0, 85, 77 });
	idle.frames.push_back({ 85, 0, 85, 77});
	idle.frames.push_back({ 170, 0, 85, 77 });
	idle.loop = true;
	idle.speed = 0.05f;

	
	// move upwards
	up.frames.push_back({ 255, 231, 85, 77 });
	up.frames.push_back({ 340, 231, 85, 77 });
	up.frames.push_back({ 425, 231, 85, 75 });
	up.frames.push_back({ 510, 231, 85, 77 });
	up.frames.push_back({ 595, 231, 85, 77 });
	up.frames.push_back({ 680, 231, 85, 77 });
	up.frames.push_back({ 765, 231, 85, 77 });
	up.frames.push_back({ 850, 231, 85, 77 });
	up.frames.push_back({ 0, 308, 85, 77 });
	up.frames.push_back({ 85, 308, 85, 77 });
	up.frames.push_back({ 170, 308, 85, 77 });
	up.frames.push_back({ 255, 308, 85, 77 });
	up.loop = true;
	up.speed = 0.25f;

	// move right
	upright.frames.push_back({ 425,462,85,77 });
	upright.frames.push_back({ 510,462,85,77 });
	upright.frames.push_back({ 595,462,85,77 });
	upright.frames.push_back({ 680,462,85,77 });
	upright.frames.push_back({ 765,462,85,77 });
	upright.frames.push_back({ 0,539,85,77 });
	upright.frames.push_back({ 85,539,85,77 });
	upright.frames.push_back({ 170,539,85,77 });
	upright.loop = true;
	upright.speed = 0.15f;


	right.frames.push_back({ 595,385,85,77 });
	right.frames.push_back({ 680,385,85,77 });
	right.frames.push_back({ 765,385,85,77 });
	right.frames.push_back({ 0,462,85,77 });
	right.frames.push_back({ 85,462,85,77 });
	right.frames.push_back({ 170,462,85,77 });
	right.frames.push_back({ 255,462,85,77 });
	right.frames.push_back({ 340,462,85,77 });
	right.loop = true;
	right.speed = 0.15f;

	// move right TODO
	down.frames.push_back({ 927,537,103,75 });
	down.frames.push_back({ 0,636,103,75 });
	down.frames.push_back({ 103,636,103,75 });
	down.frames.push_back({ 206,636,103,75 });
	down.frames.push_back({ 309,636,103,75 });
	down.frames.push_back({ 412,636,103,75 });
	down.frames.push_back({ 515,636,103,75 });
	down.frames.push_back({ 618,636,103,75 });
	down.loop = true;
	down.speed = 0.15f;

	kick.frames.push_back({ 255,0,85,77 });
	kick.frames.push_back({ 340,0,85,77 });
	kick.frames.push_back({ 425,0,85,77 });
	kick.frames.push_back({ 510,0,85,77 });
	kick.loop = true;
	kick.speed = 0.15f;

	throwWeapon.frames.push_back({ 595,0,85,77 });
	throwWeapon.frames.push_back({ 680,0,85,77 });
	throwWeapon.frames.push_back({ 765,0,85,77 });
	throwWeapon.frames.push_back({ 0,77,85,77 });
	throwWeapon.frames.push_back({ 85,77,85,77 });
	throwWeapon.frames.push_back({ 170,77,85,77 });
	throwWeapon.loop = true;
	throwWeapon.speed = 0.15f;

	attack1.frames.push_back({ 255,77,85,77 });
	attack1.frames.push_back({ 340,77,85,77 });
	attack1.frames.push_back({ 425,77,85,77 });
	attack1.loop = true;
	attack1.speed = 0.15f;

	attack2.frames.push_back({ 510,77,85,77 });
	attack2.frames.push_back({ 595,77,85,77 });
	attack2.frames.push_back({ 680,77,85,77 });
	attack2.frames.push_back({ 765,77,85,77 });
	attack2.frames.push_back({ 0,154,85,77 });
	attack2.frames.push_back({ 85,154,85,77 });
	attack2.loop = true;
	attack2.speed = 0.15f;

	attack3.frames.push_back({ 170,154,85,77 });
	attack3.frames.push_back({ 255,154,85,77 });
	attack3.frames.push_back({ 340,154,85,77 });
	attack3.loop = true;
	attack3.speed = 0.15f;

	attack4.frames.push_back({ 425,154,85,77 });
	attack4.frames.push_back({ 510,154,85,77 });
	attack4.frames.push_back({ 595,154,85,77 });
	attack4.frames.push_back({ 680,154,85,77 });
	attack4.frames.push_back({ 765,154,85,77 });
	attack4.frames.push_back({ 0,231,85,77 });
	attack4.frames.push_back({ 85,231,85,77 });
	attack4.frames.push_back({ 170,231,85,77 });
	attack4.loop = true;
	attack4.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("TMNT/arcade-transparente.png");

	destroyed = false;
	position.x = 150;
	position.y = 120;

	collider = App->collision->AddCollider({ position.x, position.y,32,14 }, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (destroyed)
		return UPDATE_CONTINUE;

	int speed = 1;


//	stateMachine.Update();
	
	//stateMachine.GetStateMap();


	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed;
		if (current_animation != &right)
		{
			upright.Reset();
			current_animation = &right;
		}
		
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		if(current_animation != &upright)
		{
			upright.Reset();
			current_animation = &upright;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		if(current_animation != &upright)
		{
			upright.Reset();
			current_animation = &upright;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT)
	{
		position.y -= speed;
		if (current_animation != &attack2)
		{
			attack2.Reset();
			current_animation = &attack2;
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{

		position.y -= speed;
		if (current_animation != &attack3)
		{
			attack3.Reset();
			current_animation = &attack3;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		/*// TODO 6: Shoot a laser using the particle system
		App->particles->AddParticle(App->particles->laser, position.x+28, position.y, 0,COLLIDER_PLAYER_SHOT);	*/

		position.y -= speed;
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
	   && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&&App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&&App->input->GetKey(SDL_SCANCODE_Q) == KEY_IDLE
		&&App->input->GetKey(SDL_SCANCODE_N) == KEY_IDLE
		&&App->input->GetKey(SDL_SCANCODE_M) == KEY_IDLE
		&&App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_IDLE)
		current_animation = &idle;

	collider->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	if(destroyed == false)
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (destroyed == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_space,0.5f);
		destroyed = true;
		//App->particles->AddParticle(App->particles->explosion, position.x, position.y,0);
	}

}