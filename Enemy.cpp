#include "Enemy.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Enemy::Enemy(EntityType entityType)
	: Entity(entityType)
{
}

Enemy::Enemy()
	:Entity()
{
}



Enemy::~Enemy()
{}

bool Enemy::Start()
{
	SDL_Rect baseColliderRect = { 0, 0, 0, 0 };
	baseCollider = App->collision->AddCollider(baseColliderRect, COLLIDER_ENEMY);
	baseCollider->SetPos(1, 2);
	return true;
}


bool Enemy::Update2()
{

	velocity.SetToZero();

	switch (status)
	{

	case IDLE:


		if (abs(App->player->position.x - position.x) > SCREEN_WIDTH / 4)
		{
			status = WALKRIGTH;
		}
		else
		{
			if (abs(App->player->position.y - position.y) > 0)
			{
				status = WALKUP;
			}
			else
			{
				if (abs(App->player->position.x - position.x) > 0)
				{
					status = WALKRIGTH;
				}
			}
		}
		break;

	case WALKUP:
		if (abs(App->player->position.x - position.x) <= SCREEN_WIDTH / 4)
		{
			if ((App->player->position.x - position.x) < 0)
				facing = LEFT;
			else
				facing = RIGHT;

			if ((App->player->position.y - position.y) < 0)
			{
				
				velocity.y = -1;
				setCurrentAnimation(&walkingLeft);

			}
			else
			{
				if ((App->player->position.y - position.y) > 0)
				{

					velocity.y = 1;
					setCurrentAnimation(&walkingLeft);

				}
				else
					status = IDLE;
			}
		}
		else
			status = IDLE;

		break;
	case WALKRIGTH:
		if (abs(App->player->position.y - position.y) == 0 || abs(App->player->position.x - position.x) > SCREEN_WIDTH / 4)
		{
			if ((App->player->position.x - position.x) < 0)
			{
				facing = LEFT;
				if (App->player->stateMachine == KNOCKED && abs(App->player->position.x - position.x) <= 150)
				{
					facing = RIGHT;
					setCurrentAnimation(&walkingLeft);
					velocity.x = 1;
					break;
				}
				else
				if (abs(App->player->position.x - position.x) <= 100 && abs(App->player->position.x - position.x) > 90)
				{
					status = ATTACKING;
					break;
				}
				if ((abs(App->player->position.x - position.x) <= 25))
				{
					status = ATTACKING;
					break;
				}
				velocity.x = -1;
				setCurrentAnimation(&walkingLeft);
			}
			else
			{
				if ((App->player->position.x - position.x) > 0)
				{
					facing = RIGHT;
					if (App->player->stateMachine == KNOCKED && abs(App->player->position.x - position.x) <= 150)
					{
						facing = LEFT;
						velocity.x = -1; //OJO CUIDAO
						setCurrentAnimation(&walkingLeft);
						break;
					}
					else 
					if (abs(App->player->position.x - position.x) <= 100 && abs(App->player->position.x - position.x) > 90)
					{
						status = ATTACKING;
						break;
					}

					if ((abs(App->player->position.x - position.x) <= 25))
					{
						status = ATTACKING;
						break;
					}
					velocity.x = 1;
					setCurrentAnimation(&walkingLeft);
				}
				else
					status = IDLE;
			}
		}
		else
			status = IDLE;
		break;

	case ATTACKING:
		if (App->player->stateMachine == BEING_HIT)
		{
			if (attackCollider != nullptr && attacking)
			{

				if (App->player->facing == facing)
					App->player->sameDirection = true;
				else
					App->player->sameDirection = false;
					
				attackCollider = App->collision->RemoveCollider(attackCollider);
				//App->player->hits += 1;

			}

			break;
		}
		if (App->player->stateMachine == KNOCKED)
		{
			if (attackCollider != nullptr)
			{
				status = IDLE;
				attackCollider = App->collision->RemoveCollider(attackCollider);
			}
		}
		if ((abs(App->player->position.x - position.x) <= 150) && abs(App->player->position.y - position.y) == 0 && current_animation != &attack2 && current_animation != &attack2Left)
		{
			if ((abs(App->player->position.x - position.x) <= 25))
			{
				if (facing == RIGHT)
				{
					if (current_animation != &attack1Left)
					{
						attacking = true;
						attackCollider = App->collision->AddCollider({ position.x + 30, position.y + 10, 45, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
						attack1Left.Reset();
						current_animation = &attack1Left;
						App->player->stateMachine = ModulePlayer::KNOCKED;
					}
				}
				else
				{
					if (current_animation != &attack1Left)
					{
						attacking = true;
						attackCollider = App->collision->AddCollider({ position.x - 15, position.y + 20, 30, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
						attack1Left.Reset();
						current_animation = &attack1Left;

						App->player->stateMachine = ModulePlayer::KNOCKED;
					}
				}
			}
			else
			{
				if ((abs(App->player->position.x - position.x) <= 100) && (abs(App->player->position.x - position.x) > 90))
				{
					if (enemyType == PURPLE)
					{
						if (facing  == RIGHT)
						{
							if (current_animation != &attack2Left)
							{
								attacking = true;
								jumped = true;
								attackCollider = App->collision->AddCollider({ position.x + 30, position.y + 20, 30, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
								attack2Left.Reset();
								current_animation = &attack2Left;
							}
						}
						else
						{
							if (current_animation != &attack2Left)
							{
								attacking = true;
								jumped = true;
								attackCollider = App->collision->AddCollider({ position.x - 30, position.y + 20, 30, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
								attack2Left.Reset();
								current_animation = &attack2Left;
							}
						}
					}
					else
					{
						if (facing == RIGHT)
						{
							if (current_animation != &attack2Left)
							{
								App->particles->AddParticle(App->particles->shuriken, position.x + 25, position.y + 10, 3, COLLIDER_ENEMY_SHOT);
								attacking = true;
								attack2Left.Reset();
								attackCollider = App->collision->AddCollider({ position.x + 30, position.y + 20, 30, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
								current_animation = &attack2Left;
							}
						}
						else
						{
							if (current_animation != &attack2Left)
							{
								App->particles->AddParticle(App->particles->shuriken, position.x - 25, position.y + 10, -3, COLLIDER_ENEMY_SHOT);
								attacking = true;
								attack2Left.Reset();
								attackCollider = App->collision->AddCollider({ position.x - 30, position.y + 20, 30, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
								current_animation = &attack2Left;
							}
						}
					}
				}
			}

		}
		else
		{
			if (!jumped && !attacking)
				status = IDLE;
		}


		if (jumped)
		{
			if (facing = RIGHT)
			{
				if (abs(App->player->position.x - position.x) <= 25)
				{
					jumped = false;
					attackCollider = App->collision->RemoveCollider(attackCollider);
					attacking = false;
					status = IDLE;

				}
				if (attackCollider != nullptr)
				{
					attackCollider->SetPos(position.x + 30, position.y + 20);
				}
				velocity.x += 3;
			}
			else
			{
				if (abs(App->player->position.x - position.x) <= 25)
				{
					jumped = false;
					attackCollider = App->collision->RemoveCollider(attackCollider);
					attacking = false;
					status = IDLE;
				}
				if (attackCollider != nullptr)
				{
					attackCollider->SetPos(position.x - 15, position.y + 20);
				}
				velocity.x -= 3;
			}


		}
		if ((current_animation == &attack1 || current_animation == &attack1Left || current_animation == &attack2 || current_animation == &attack2Left) && current_animation->Finished())
		{
			jumped = false;
			current_animation = &walkingLeft;
			attacking = false;
			status = IDLE;
			if (attackCollider != nullptr)
				attackCollider = App->collision->RemoveCollider(attackCollider);
		}
		break;

	case BEING_HIT:
		if (attacking)
		{
			attacking = false;
			if (attackCollider != nullptr)
				attackCollider = App->collision->RemoveCollider(attackCollider);
		}

		if (App->player->facing == facing)
			App->player->sameDirection = true;
		else
			App->player->sameDirection = false;

		if (consecutiveHits >= 2)
		{
			status = KNOCKED;
			break;
		}
		if (facing == RIGHT)
		{

			consecutiveHits += 1;
			setCurrentAnimation(&beingHit);
		}
		else
		{

			consecutiveHits += 1;
			setCurrentAnimation(&beingHit2);
		}
		if ((current_animation == &beingHit || current_animation == &beingHit2) && current_animation->Finished())
		{
			status = IDLE;
		}
		break;

	case KNOCKED:
		cont += 1;
		if (facing == RIGHT)
		{
			if (App->player->sameDirection)
			{
				position.x += 2;
				setCurrentAnimation(&beingHit3);
			}
			else
			{
				position.x -= 2;
				setCurrentAnimation(&beingHit4);

			}
		}
		else
		{
			if (App->player->sameDirection)
			{
				position.x -= 2;
				setCurrentAnimation(&beingHit5);
			}
			else
			{
				position.x += 2;
				setCurrentAnimation(&beingHit6);
			}
		}

		if (cont == 2) status = DEAD;

		break;

	case DEAD:
		if ((current_animation == &beingHit3 || current_animation == &beingHit4 || current_animation == &beingHit5 || current_animation == &beingHit6) && current_animation->Finished())
		{
			dead = true;
		}
		break;

	case UNKNOWN:
		spawn();
		break;
	}

	position += velocity;
	return true;
}

update_status Enemy::Update()
{
//	handleState();

	if (status != IDLE) {
		//updatePosition();
		spawn();
	}

	return UPDATE_CONTINUE;
}

// Respawn player
void Enemy::spawn()
{
	LOG("Spawning Enemy");
	//position = initPos;
	//height = 0;
	setCurrentAnimation(&walkingLeft);
	status = IDLE;
	
}

bool Enemy::isAttacking() const {
	return (status == ATTACKING || status == ATTACK_JMP);
}

bool Enemy::canBeAttacked() const {
	return (status != State::BEING_HIT && status != State::BEING_HIT_2_INI
		&& status != State::BEING_HIT_2 && status != State::BEING_HIT_2_END);
}

void Enemy::setCurrentAnimation(Animation* anim) {
	if (current_animation != anim)
	{
		anim->Reset();
		current_animation = anim;
	}
}



