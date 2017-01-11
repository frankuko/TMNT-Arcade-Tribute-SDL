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

	


	// move right
	up.frames.push_back({ 425,462,85,77 });
	up.frames.push_back({ 510,462,85,77 });
	up.frames.push_back({ 595,462,85,77 });
	up.frames.push_back({ 680,462,85,77 });
	up.frames.push_back({ 765,462,85,77 });
	up.frames.push_back({ 0,539,85,77 });
	up.frames.push_back({ 85,539,85,77 });
	up.frames.push_back({ 170,539,85,77 });
	up.loop = true;
	up.speed = 0.15f;


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

	// move upwards
	jump.frames.push_back({ 255, 231, 85, 77 });
	jump.frames.push_back({ 340, 231, 85, 77 });
	jump.frames.push_back({ 425, 231, 85, 75 });
	jump.frames.push_back({ 510, 231, 85, 77 });
	jump.frames.push_back({ 595, 231, 85, 77 });
	jump.frames.push_back({ 680, 231, 85, 77 });
	jump.frames.push_back({ 765, 231, 85, 77 });
	jump.frames.push_back({ 850, 231, 85, 77 });
	jump.frames.push_back({ 0, 308, 85, 77 });
	jump.frames.push_back({ 85, 308, 85, 77 });
	jump.frames.push_back({ 170, 308, 85, 77 });
	jump.frames.push_back({ 255, 308, 85, 77 });
	jump.loop = true;
	jump.speed = 0.25f;


	jumpAttack1.frames.push_back({ 340,308,85,77 });
	jumpAttack1.frames.push_back({ 425,308,85,77 });
	jumpAttack1.frames.push_back({ 510,308,85,77 });
	jumpAttack1.loop = true;
	jumpAttack1.speed = 0.15f;


	jumpAttack2.frames.push_back({ 595,308,85,77 });
	jumpAttack2.frames.push_back({ 680,308,85,77 });
	jumpAttack2.frames.push_back({ 765,308,85,77 });
	jumpAttack2.loop = true;
	jumpAttack2.speed = 0.15f;

	jumpAttack3.frames.push_back({ 0,385,85,77 });
	jumpAttack3.frames.push_back({ 85,385,85,77 });
	jumpAttack3.frames.push_back({ 170,385,85,77 });
	jumpAttack3.frames.push_back({ 255,385,85,77 });
	jumpAttack3.frames.push_back({ 340,385,85,77 });
	jumpAttack3.frames.push_back({ 425,385,85,77 });
	jumpAttack3.frames.push_back({ 510,385,85,77 });
	jumpAttack3.loop = true;
	jumpAttack3.speed = 0.15f;

	hit1.frames.push_back({ 255,539,85,77 });
	hit1.frames.push_back({ 340,539,85,77 });
	hit1.frames.push_back({ 425,539,85,77 });
	hit1.frames.push_back({ 510,539,85,77 });
	hit1.frames.push_back({ 595,539,85,77 });
	hit1.frames.push_back({ 680,539,85,77 });
	hit1.loop = true;
	hit1.speed = 0.15f;

	hit2.frames.push_back({ 765,616,85,77 });
	hit2.frames.push_back({ 0,616,85,77 });
	hit2.frames.push_back({ 85,616,85,77 });
	hit2.frames.push_back({ 170,616,85,77 });
	hit2.loop = true;
	hit2.speed = 0.15f;

	hit3.frames.push_back({ 255,616,85,77 });
	hit3.frames.push_back({ 340,616,85,77 });
	hit3.frames.push_back({ 425,616,85,77 });
	hit3.frames.push_back({ 510,616,85,77 });
	hit3.frames.push_back({ 595,616,85,77 });
	hit3.frames.push_back({ 680,616,85,77 });
	hit3.frames.push_back({ 765,616,85,77 });
	hit3.frames.push_back({ 0,693,85,77 });
	hit3.frames.push_back({ 85,693,85,77 });
	hit3.frames.push_back({ 170,693,85,77 });
	hit3.loop = true;
	hit3.speed = 0.15f;

	hitBehind1.frames.push_back({ 255,693,85,77 });
	hitBehind1.frames.push_back({ 340,693,85,77 });
	hitBehind1.frames.push_back({ 425,693,85,77 });
	hitBehind1.loop = true;
	hitBehind1.speed = 0.15f;

	hitBehind2.frames.push_back({ 510,693,85,77 });
	hitBehind2.frames.push_back({ 595,693,85,77 });
	hitBehind2.frames.push_back({ 680,693,85,77 });
	hitBehind2.frames.push_back({ 765,693,85,77 });
	hitBehind2.frames.push_back({ 0,770,85,77 });
	hitBehind2.frames.push_back({ 85,770,85,77 });
	hitBehind2.frames.push_back({ 170,770,85,77 });
	hitBehind2.frames.push_back({ 255,770,85,77 });
	hitBehind2.frames.push_back({ 340,770,85,77 });
	hitBehind2.frames.push_back({ 425,770,85,77 });
	hitBehind2.frames.push_back({ 510,770,85,77 });
	hitBehind2.frames.push_back({ 595,770,85,77 });
	//hitBehind2.frames.push_back({ 680,770,85,77 });
	//hitBehind2.frames.push_back({ 765,770,85,77 });
	hitBehind2.loop = true;
	hitBehind2.speed = 0.15f;

	hitBehind3.frames.push_back({ 0,847,85,77 });
	hitBehind3.frames.push_back({ 85,847,85,77 });
	hitBehind3.frames.push_back({ 170,847,85,77 });
	hitBehind3.frames.push_back({ 255,847,85,77 });
	hitBehind3.frames.push_back({ 340,847,85,77 });
	hitBehind3.frames.push_back({ 425,847,85,77 });
	hitBehind3.frames.push_back({ 510,847,85,77 });
	hitBehind3.frames.push_back({ 595,847,85,77 });
	hitBehind3.frames.push_back({ 680,847,85,77 });
	hitBehind3.frames.push_back({ 765,847,85,77 });
	hitBehind3.loop = true;
	hitBehind3.speed = 0.15f;



}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("TMNT/arcade-transparente.png");

	destroyed = false;
	position.x = 30;
	position.y = 120;

	collider = App->collision->AddCollider({ position.x, position.y,40,50 }, COLLIDER_PLAYER, this);
	stateMachine = IDLE;
	feetCollider = App->collision->AddCollider({ position.x+25, position.y + 70, 30, 5 }, COLLIDER_PLAYER_FEET, this);

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

	int speed = 2;


//	stateMachine.Update();
	
	//stateMachine.GetStateMap();


	switch (stateMachine)
	{

	case IDLE:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			facing = LEFT;


			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				setCurrentAnimation(&up);
			}
			else
			{
				setCurrentAnimation(&right);

			}



			position.x -= speed;

		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			facing = RIGHT;

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				setCurrentAnimation(&up);
			}
			else
			{
				setCurrentAnimation(&right);
			}

			position.x += speed;

		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += speed;
			setCurrentAnimation(&up);

		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y -= speed;
			setCurrentAnimation(&up);
		}

		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
		{
			//position.y -= speed;
			stateMachine = ATTACKING;
			setCurrentAnimation(&attack1);
		}


		if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
		{

			stateMachine = ATTACKING_2;
			setCurrentAnimation(&attack2);
		}

		if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		{

			stateMachine = ATTACKING_3;
			if (facing == RIGHT)
				position.x += speed * 3;
			else
				position.x -= speed * 3;
			setCurrentAnimation(&attack3);
		}

		if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
		{

			stateMachine = ATTACKING_4;
			setCurrentAnimation(&attack4);
		}



		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			/*// TODO 6: Shoot a laser using the particle system
			App->particles->AddParticle(App->particles->laser, position.x+28, position.y, 0,COLLIDER_PLAYER_SHOT);	*/
			stateMachine = JUMP_INI;
			setCurrentAnimation(&jump);
		}

		break;

	case JUMP_INI:
		setCurrentAnimation(&jump);
		initPosition = position;
		destinyPosition.y = position.y - 40;
		destinyPosition.x = position.x;
		stateMachine = JUMPING;
		feetCollider = App->collision->RemoveCollider(feetCollider);
		
		break;

	case JUMPING:

		setCurrentAnimation(&jump);
		if (position.y <= destinyPosition.y)
		{
			stateMachine = JUMP_END;
		}

		else
		{
			//seguimos subiendo
			position.y -= 3;
		}

		break;

	case JUMP_END:
		setCurrentAnimation(&jump);
		if (position.y >= initPosition.y)
		{
			feetCollider = App->collision->AddCollider({ position.x + 25, position.y + 70, 30, 5 }, COLLIDER_PLAYER_FEET, this);
			stateMachine = IDLE;
		}

		else
		{
			position.y += 3;
		}

		break;

	case KNOCKED:
		setCurrentAnimation(&hit1);
		hits += 1;
		//
		if (hits >= 5*50)
		{
			stateMachine = DEAD;
			break;
		}

		if (current_animation->Finished())
		{

			stateMachine = IDLE;
			break;
		}
	case ATTACKING:
		if (current_animation->Finished()) 
		{
			
			stateMachine = IDLE;
			break;
		}

		/*if (facing == RIGHT)
		{
			weaponCollider = App->collision->AddCollider({ position.x + 50, position.y + 60, 30, 5 }, COLLIDER_PLAYER_WEAPON, this);
		}
		else
		{
			weaponCollider = App->collision->AddCollider({ position.x + 5, position.y + 60, 30, 5 }, COLLIDER_PLAYER_WEAPON, this);
		}*/

		 

		break;
	case ATTACKING_2:
		if (current_animation->Finished())
		{

			stateMachine = IDLE;
			break;
		}

		break;
	case ATTACKING_3:
		if (current_animation->Finished())
		{

			stateMachine = IDLE;
			break;
		}

		break;
	case ATTACKING_4:
		if (current_animation->Finished())
		{

			stateMachine = IDLE;
			break;
		}

		break;


	case DEAD:

		setCurrentAnimation(&hitBehind2);
		//destroyed = true;
		if (current_animation->Finished())
		{
			destroyed = true;
			//stateMachine = IDLE;
			break;
		}



	default:
		break;
	}




	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
	   && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE
		&& App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE
		&&App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE
		&& stateMachine == IDLE)
		current_animation = &idle;


	// Draw everything --------------------------------------



	if (destroyed == false)
	{
		if (facing == LEFT) 
		{
			collider->SetPos(position.x+20, position.y + 20);
			if(feetCollider != nullptr)
				feetCollider->SetPos(position.x + 25, position.y + 70);
			App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 1.0f, true);

		}
		else
		{
			collider->SetPos(position.x + 20, position.y + 20);
			if (feetCollider != nullptr)
				feetCollider->SetPos(position.x + 25, position.y + 70);
			App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		}
			


	}
	else 
	{
		hits = 0;
		App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_level,0.5f);
	}
		
	
		

	return UPDATE_CONTINUE;
}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (destroyed == true)
	{
		hits = 0;
	//	App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_level,0.5f);
		//App->CleanUp();
		//destroyed = true;
		//App->particles->AddParticle(App->particles->explosion, position.x, position.y,0);
	}

	//left
	if ((c1->rect.x < c2->rect.x + c2->rect.w) && ((c2->rect.x + c2->rect.w) - c1->rect.x) < c1->rect.w && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && (c2->type == COLLIDER_WALL) && (c1->type == COLLIDER_PLAYER_FEET))
	{
		position.x += ((c2->rect.x + c2->rect.w) - c1->rect.x);
	}
	else
	{
		//right
		if (c1->rect.x + c1->rect.w > c2->rect.x && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && (c2->type == COLLIDER_WALL) && (c1->type == COLLIDER_PLAYER_FEET))
		{
			position.x += (c2->rect.x - (c1->rect.x + c1->rect.w));
		}
		else
			//down
			if ((c1->rect.y < c2->rect.y + c2->rect.h) && ((c1->rect.h + c1->rect.y) - c2->rect.y) > c1->rect.h && (c2->type == COLLIDER_WALL) && (c1->type == COLLIDER_PLAYER_FEET))
			{
				position.y += ((c2->rect.y + c2->rect.h) - c1->rect.y);
			}
			else
			
				//up
				if (c1->rect.h + c1->rect.y > c2->rect.y && (c2->type == COLLIDER_WALL ) && (c1->type == COLLIDER_PLAYER_FEET))
				{
					position.y += (c2->rect.y - (c1->rect.h + c1->rect.y));
				}
			
		
	}

}

void ModulePlayer::setCurrentAnimation(Animation* anim) {
	if (current_animation != anim)
	{
		anim->Reset();
		current_animation = anim;
	}
}