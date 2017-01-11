#include "ModuleEnemy.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePLayer.h"
#include "ModuleCollision.h"

ModuleEnemy::ModuleEnemy(bool active) : Module(active)
{

	//Animaciones de cada enemigo y sonidos. Prototipos

	//ENEMY 1

	//going left


	/*enemy1.walkingLeft.frames.push_back({ 0, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 80, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 160, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 240, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 320, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 0, 80, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 80, 80, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 160, 80, 80, 80 });*/


	enemy1.walkingLeft.frames.push_back({ 160, 80, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 80, 80, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 0, 80, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 320, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 240, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 160, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 80, 0, 80, 80 });
	enemy1.walkingLeft.frames.push_back({ 0, 0, 80, 80 });













	

	enemy1.walkingLeft.pivotY = -5;
	enemy1.walkingLeft.loop = true;
	enemy1.walkingLeft.speed = 0.2f;

	//going right
	/*enemy1.walkingRight.frames.push_back({ 589, 80, 52, 64 });
	enemy1.walkingRight.frames.push_back({ 671, 80, 52, 64 });
	enemy1.walkingRight.frames.push_back({ 757, 80, 52, 64 });
	enemy1.walkingRight.frames.push_back({ 433, 0, 52, 64 });
	enemy1.walkingRight.frames.push_back({ 508, 0, 52, 64 });
	enemy1.walkingRight.frames.push_back({ 593, 0, 52, 64 });
	enemy1.walkingRight.frames.push_back({ 674, 0, 52, 64 });
	enemy1.walkingRight.frames.push_back({ 751, 0, 52, 64 });
	enemy1.walkingRight.pivotY = -5;
	enemy1.walkingRight.loop = true;
	enemy1.walkingRight.speed = 0.2f;*/

	//going upLeft
	enemy1.upLeft.frames.push_back({ 0, 240, 80, 80 });
	enemy1.upLeft.frames.push_back({ 320, 160, 80, 80 });
	enemy1.upLeft.frames.push_back({ 240, 160, 80, 80 });
	enemy1.upLeft.frames.push_back({ 160, 160, 80, 80 });
	enemy1.upLeft.frames.push_back({ 80, 160, 80, 80 });
	enemy1.upLeft.frames.push_back({ 0, 160, 80, 80 });
	enemy1.upLeft.frames.push_back({ 320, 80, 80, 80 });
	enemy1.upLeft.frames.push_back({ 240, 80, 80, 80 });
	enemy1.upLeft.pivotY = -5;
	enemy1.upLeft.loop = true;
	enemy1.upLeft.speed = 0.2f;

	//going up
	enemy1.up.frames.push_back({ 749, 240, 52, 64 });
	enemy1.up.frames.push_back({ 431, 160, 52, 64 });
	enemy1.up.frames.push_back({ 509, 160, 52, 64 });
	enemy1.up.frames.push_back({ 595, 160, 52, 64 });
	enemy1.up.frames.push_back({ 671, 160, 52, 64 });
	enemy1.up.frames.push_back({ 753, 160, 52, 64 });
	enemy1.up.frames.push_back({ 433, 81, 52, 64 });
	enemy1.up.frames.push_back({ 512, 81, 52, 64 });
	enemy1.up.pivotY = -5;
	enemy1.up.loop = true;
	enemy1.up.speed = 0.2f;

	//attack1
	enemy1.attack1.frames.push_back({ 577, 643, 60, 64 });
	enemy1.attack1.frames.push_back({ 668, 643, 60, 64 });
	enemy1.attack1.frames.push_back({ 753, 643, 60, 64 });
	enemy1.attack1.pivotY = -10;
	enemy1.attack1.loop = false;
	enemy1.attack1.speed = 0.07f;

	//attack1Left
	enemy1.attack1Left.frames.push_back({ 16, 643, 60, 64 });
	enemy1.attack1Left.frames.push_back({ 80, 643, 60, 64 });
	enemy1.attack1Left.frames.push_back({ 0, 643, 60, 64 });
	enemy1.attack1Left.pivotY = -10;
	enemy1.attack1Left.loop = false;
	enemy1.attack1Left.speed = 0.07f;

	//attack2
	enemy1.attack2.frames.push_back({ 417, 478, 60, 64 });
	enemy1.attack2.frames.push_back({ 496, 478, 60, 64 });
	enemy1.attack2.frames.push_back({ 571, 478, 60, 64 });
	enemy1.attack2.frames.push_back({ 571, 478, 60, 64 });
	enemy1.attack2.frames.push_back({ 571, 478, 60, 64 });
	enemy1.attack2.frames.push_back({ 571, 478, 60, 64 });
	enemy1.attack2.pivotY = -10;
	enemy1.attack2.loop = false;
	enemy1.attack2.speed = 0.15f;

	//attack2Left
	enemy1.attack2Left.frames.push_back({ 326, 478, 60, 64 });
	enemy1.attack2Left.frames.push_back({ 242, 478, 60, 64 });
	enemy1.attack2Left.frames.push_back({ 160, 478, 60, 64 });
	enemy1.attack2Left.frames.push_back({ 160, 478, 60, 64 });
	enemy1.attack2Left.frames.push_back({ 160, 478, 60, 64 });
	enemy1.attack2Left.frames.push_back({ 160, 478, 60, 64 });
	enemy1.attack2Left.pivotY = -10;
	enemy1.attack2Left.loop = false;
	enemy1.attack2Left.speed = 0.15f;

	//beingHit
	enemy1.beingHit.frames.push_back({ 250, 800, 60, 64 });
	enemy1.beingHit.frames.push_back({ 167, 800, 60, 64 });
	enemy1.beingHit.frames.push_back({ 81, 800, 60, 64 });
	enemy1.beingHit.frames.push_back({ 9, 800, 60, 64 });
	enemy1.beingHit.pivotY = -10;
	enemy1.beingHit.loop = false;
	enemy1.beingHit.speed = 0.2f;

	//beingHit2
	enemy1.beingHit2.frames.push_back({ 508, 800, 60, 64 });
	enemy1.beingHit2.frames.push_back({ 584, 800, 60, 64 });
	enemy1.beingHit2.frames.push_back({ 658, 800, 60, 64 });
	enemy1.beingHit2.frames.push_back({ 746, 800, 60, 64 });
	enemy1.beingHit2.pivotY = -10;
	enemy1.beingHit2.loop = false;
	enemy1.beingHit2.speed = 0.2f;

	//beingHit3
	enemy1.beingHit3.frames.push_back({ 16, 1940, 60, 64 });
	enemy1.beingHit3.frames.push_back({ 99, 1940, 60, 64 });
	enemy1.beingHit3.frames.push_back({ 99, 1940, 60, 64 });
	enemy1.beingHit3.frames.push_back({ 99, 1940, 60, 64 });
	enemy1.beingHit3.frames.push_back({ 99, 1940, 60, 64 });
	enemy1.beingHit3.frames.push_back({ 253, 1855, 60, 64 });
	enemy1.beingHit3.frames.push_back({ 329, 1855, 60, 64 });
	enemy1.beingHit3.pivotY = -20;
	enemy1.beingHit3.loop = false;
	enemy1.beingHit3.speed = 0.2f;

	//beingHit4
	enemy1.beingHit4.frames.push_back({ 738, 1940, 60, 64 });
	enemy1.beingHit4.frames.push_back({ 663, 1940, 60, 64 });
	enemy1.beingHit4.frames.push_back({ 663, 1940, 60, 64 });
	enemy1.beingHit4.frames.push_back({ 663, 1940, 60, 64 });
	enemy1.beingHit4.frames.push_back({ 663, 1940, 60, 64 });
	enemy1.beingHit4.frames.push_back({ 498, 1855, 60, 64 });
	enemy1.beingHit4.frames.push_back({ 414, 1855, 60, 64 });
	enemy1.beingHit4.pivotY = -20;
	enemy1.beingHit4.loop = false;
	enemy1.beingHit4.speed = 0.2f;

	//beingHit5
	enemy1.beingHit5.frames.push_back({ 332, 1940, 60, 64 });
	enemy1.beingHit5.frames.push_back({ 251, 1940, 60, 64 });
	enemy1.beingHit5.frames.push_back({ 171, 1940, 60, 64 });
	enemy1.beingHit5.frames.push_back({ 17, 2016, 60, 64 });
	enemy1.beingHit5.frames.push_back({ 91, 2016, 60, 64 });
	enemy1.beingHit5.frames.push_back({ 159, 1998, 60, 64 });
	enemy1.beingHit5.pivotY = -20;
	enemy1.beingHit5.loop = false;
	enemy1.beingHit5.speed = 0.2f;

	//beingHit6
	enemy1.beingHit6.frames.push_back({ 418, 1940, 60, 64 });
	enemy1.beingHit6.frames.push_back({ 498, 1940, 60, 64 });
	enemy1.beingHit6.frames.push_back({ 576, 1940, 60, 64 });
	enemy1.beingHit6.frames.push_back({ 565, 2016, 60, 64 });
	enemy1.beingHit6.frames.push_back({ 657, 2016, 60, 64 });
	enemy1.beingHit6.frames.push_back({ 740, 1998, 60, 64 });
	enemy1.beingHit6.pivotY = -20;
	enemy1.beingHit6.loop = false;
	enemy1.beingHit6.speed = 0.2f;

}

ModuleEnemy::~ModuleEnemy()
{
}

bool ModuleEnemy::Start()
{
	LOG("Loading enemies");
	enemy1.graphics = App->textures->Load("TMNT/purple-trans.png");
	enemy2.graphics = App->textures->Load("TMNT/orange.png");

	return true;
}

update_status ModuleEnemy::Update()
{

	for (list<Enemy*>::iterator it = active.begin(); it != active.end();)
	{
		Enemy* e = *it;

		if (e->dead == true)
		{
			e->baseCollider = App->collision->RemoveCollider(e->baseCollider);
			e->feetCollider = App->collision->RemoveCollider(e->feetCollider);
			active.remove(e);
			delete e;
			if (active.empty())
			{
				enemiesClear = true;
			}
			break;
		}
		else
		{
			if (e->Update2() == false)
			{
				RELEASE(*it);
				it = active.erase(it);
			}
			else
			{
				e->feetCollider->SetPos(e->position.x + 10, e->position.y + 50);
				e->baseCollider->SetPos(e->position.x + 10, e->position.y + 5);
				//posibles fallos, current animation y graphics

				if(e->facing == Enemy::RIGHT)
					App->renderer->Blit(e->graphics, e->position.x, e->position.y - e->current_animation->pivotY, &(e->current_animation->GetCurrentFrame()),1,true);
				else
					App->renderer->Blit(e->graphics, e->position.x, e->position.y - e->current_animation->pivotY, &(e->current_animation->GetCurrentFrame()));

				++it;
			}
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");
	if (enemy1.graphics != NULL)
		App->textures->Unload(enemy1.graphics);

	for (list<Enemy*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}

void ModuleEnemy::AddEnemy(const Enemy & enemy, iPoint position, Enemy::EnemyType type)
{
	Enemy* e = new Enemy(enemy);
	e->position.x = position.x;
	e->position.y = position.y;
	e->enemyType = type;
	e->feetCollider = App->collision->AddCollider({ position.x, position.y + 50, 32, 14 }, COLLIDER_PLAYER_FEET, this);
	e->baseCollider = App->collision->AddCollider({ position.x, position.y + 10, 32, 45 }, COLLIDER_ENEMY, this);
	active.push_back(e);
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{


	for (list<Enemy*>::iterator it = active.begin(); it != active.end();)
	{
		Enemy* aux = *it;


		
		/*if (App->player->jumped)
		{
			if (c2->type == COLLIDER_PLAYER_WEAPON && c1 == aux->baseCollider && aux->status != Enemy::KNOCKED)
			{
				aux->status = Enemy::BEING_HIT;
			}
		}
		else
		{
			if (c2->type == COLLIDER_PLAYER_WEAPON && c1 == aux->baseCollider && abs(App->player->position.y - aux->position.y)<15 && aux->status != Enemy::KNOCKED)
			{
				aux->status = Enemy::BEING_HIT;
			}
		}
		//left
		if ((c1->rect.x < c2->rect.x + c2->rect.w) && ((c2->rect.x + c2->rect.w) - c1->rect.x) < c1->rect.w && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && (c2->type == COLLIDER_WALL))
		{
			aux->position.x += ((c2->rect.x + c2->rect.w) - c1->rect.x);
		}
		else
		{
			//right
			if (c1->rect.x + c1->rect.w > c2->rect.x && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && (c2->type == COLLIDER_WALL))
			{
				aux->position.x += (c2->rect.x - (c1->rect.x + c1->rect.w));
			}
			else
			{
				//down
				if ((c1->rect.y < c2->rect.y + c2->rect.h) && ((c1->rect.h + c1->rect.y) - c2->rect.y) > c1->rect.h && (c2->type == COLLIDER_WALL))
				{
					aux->position.y += ((c2->rect.y + c2->rect.h) - c1->rect.y);
				}
				else
				{
					//up
					if (c1->rect.h + c1->rect.y > c2->rect.y && (c2->type == COLLIDER_WALL))
					{
						aux->position.y += (c2->rect.y - (c1->rect.h + c1->rect.y));
					}
				}
			}
		}*/
		++it;
	}
}