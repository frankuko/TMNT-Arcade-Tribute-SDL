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

	case JUMPING:
		break;
	case WALKUP:
		if (abs(App->player->position.x - position.x) <= SCREEN_WIDTH / 4)
		{
			if ((App->player->position.y - position.y) < 0)
			{

				velocity.y = -1;
				if (facing == RIGHT) setCurrentAnimation(&up);
				else setCurrentAnimation(&upLeft);

			}
			else
			{
				if ((App->player->position.y - position.y) > 0)
				{

					velocity.y = 1;
					if (facing == RIGHT) setCurrentAnimation(&walkingRight);
					else setCurrentAnimation(&walkingLeft);

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
				//SI EL JUGADOR ESTA EN EL SUELO
				if (App->player->stateMachine == KNOCKED && abs(App->player->position.x - position.x) <= 150)
				{
					facing = RIGHT;
					setCurrentAnimation(&walkingRight);
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
					else if (abs(App->player->position.x - position.x) <= 100 && abs(App->player->position.x - position.x) > 90)
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
					setCurrentAnimation(&walkingRight);
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
				App->player->hits += 1;

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
					if (current_animation != &attack1)
					{
						attacking = true;
						attackCollider = App->collision->AddCollider({ position.x + 30, position.y + 10, 45, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
						attack1.Reset();
						current_animation = &attack1;
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
							if (current_animation != &attack2)
							{
								attacking = true;
								jumped = true;
								attackCollider = App->collision->AddCollider({ position.x + 30, position.y + 20, 30, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
								attack2.Reset();
								current_animation = &attack2;
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
							if (current_animation != &attack2)
							{
								App->particles->AddParticle(App->particles->shuriken, position.x + 25, position.y + 10, 3, COLLIDER_ENEMY_SHOT);
								attacking = true;
								attack2.Reset();
								attackCollider = App->collision->AddCollider({ position.x + 30, position.y + 20, 30, 15 }, COLLIDER_ENEMY_WEAPON, (Module*)App->enemy);
								current_animation = &attack2;
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
			current_animation = &walkingRight;
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
/*
void Enemy::hit(Entity* c2) {

	if (hitTimer.getDelta() < 500) {
		++consecutiveHits;
	}

	else consecutiveHits = 0;

	if (c2->position.x > position.x) {
		c2->facing = LEFT;
	}
	else {
		c2->facing = RIGHT;
	}
	if (height > 0 || c2->height > 0) {
		c2->setCurrentAnimation(&(c2->beingHit3));
		c2->status = BEING_HIT_2_INI;
	}
	else {
		switch (consecutiveHits) {
		case 0:
		case 1:
			this->setCurrentAnimation(&chop);
			this->status = ATTACKING;
			c2->setCurrentAnimation(&(c2->beingHit));
			c2->status = BEING_HIT;
			break;
		case 2:
			this->setCurrentAnimation(&kick);
			this->status = ATTACKING;
			c2->setCurrentAnimation(&(c2->beingHit2));
			c2->status = BEING_HIT;
			break;
		case 3:
			this->setCurrentAnimation(&chop);
			this->status = ATTACKING;
			c2->setCurrentAnimation(&(c2->beingHit3));
			c2->status = BEING_HIT_2_INI;
			break;
		}
		hitTimer.reset();
		c2->beingHitTimer.reset();
	}
}*/

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
/*
void Enemy::handleState()
{
	switch (status) {
	case UNKNOWN:
		//if (App->scene_stage->stageState == LEVEL)
		spawn();
		break;

	case RESPAWNING:
		setCurrentAnimation(&respawning);
		if (height > 0)
			verticalForce += 0.3f;
		else {
			respawning.speed = 1.0f;
			if (EnemyTimer.getDelta() >= 100) {
				status = IDLE;
				setCurrentAnimation(&idle);
			}
		}
		break;

	case IDLE:
		if (velocity.x != 0.0f || velocity.y != 0.0f) {
			status = WALK;
			setCurrentAnimation(&walking);
		}
		break;

	case WALK:
		if (velocity.x > 0) facing = RIGHT;
		else if (velocity.x < 0) facing = LEFT;
		if (velocity.x == 0.0f && velocity.y == 0.0f) {
			status = IDLE;
			setCurrentAnimation(&idle);
		}
		break;

	case JUMP_INI:
		if (jumpTimer.getDelta() >= 100) {
			verticalForce = -8.0f;
			jumping.speed = 1.0f;
			height = 0;
			status = JUMPING;
		}
		break;

	case JUMPING:
		if (height > 0) {
			verticalForce += 0.5f;
		}
		else {
			jumping.speed = 0.0f;
			jumping.Reset();
			prevVelocity = velocity;
			velocity.y = 0.0f;
			velocity.x = 0.0f;
			status = JUMP_END;
			jumpTimer.reset();
		}
		break;

	case ATTACK_JMP:
		if (height > 0)
			verticalForce += 0.5f;
		else {
			jumping.speed = 0.0f;
			jumping.Reset();
			prevVelocity = velocity;
			velocity.y = 0.0f;
			velocity.x = 0.0f;
			setCurrentAnimation(&jumping);
			status = JUMP_END;
			jumpTimer.reset();
		}
		break;

	case ATTACKING:
		if (attackTimer.getDelta() >= chop.frames.size() * 100) {
			velocity += prevVelocity;
			if (velocity.x != 0.0f || velocity.y != 0.0f) {
				status = WALK;
				setCurrentAnimation(&walking);
			}
			else {
				status = IDLE;
				setCurrentAnimation(&idle);
			}
		}
		break;

	case JUMP_END:
		if (jumpTimer.getDelta() >= 100) {
			velocity += prevVelocity;
			if (velocity.x != 0.0f || velocity.y != 0.0f) {
				status = WALK;
				setCurrentAnimation(&walking);
			}
			else {
				status = IDLE;
				setCurrentAnimation(&idle);
			}
		}
		break;

	case BEING_HIT:
		if (beingHitTimer.getDelta() >= 300) {
			status = IDLE;
			setCurrentAnimation(&idle);
		}
		break;

	case BEING_HIT_2_INI:
		verticalForce = -5.0f;
		if (facing == RIGHT) {
			horizontalForce = -5.0f;
		}
		else {
			horizontalForce = 5.0f;
		}
		status = BEING_HIT_2;
		break;

	case BEING_HIT_2:
		if (height > 0) {
			verticalForce += 0.5f;
		}
		else {
			verticalForce = 0;
			horizontalForce = 0;
			status = BEING_HIT_2_END;
			beingHitTimer.reset();
		}
		break;

	case BEING_HIT_2_END:
		if (beingHitTimer.getDelta() >= (gettingUp.frames.size() - 1) * 10 / gettingUp.speed + 1100) {
			// remember to check that it might be dead
			status = IDLE;
			setCurrentAnimation(&idle);
		}
		else if (beingHitTimer.getDelta() >= 400) {
			setCurrentAnimation(&gettingUp);
		}
		else setCurrentAnimation(&knockedOut);
		break;
	}
}*/

/*void Enemy::updatePosition() {
	if (status == IDLE || status == WALK || status == JUMPING || status == ATTACK_JMP)
		position.x += (int)velocity.x;
	if (position.x < 0)
		position.x = 0;
	if (height == 0 && status != JUMPING && status != ATTACKING && status != BEING_HIT_2
		&& status != BEING_HIT_2_END && status != BEING_HIT && status != BEING_HIT_2_INI)
		depth -= (int)velocity.y;
	if (status == IDLE || status == WALK)
		position.y += (int)velocity.y;
	if (status == RESPAWNING || status == JUMPING || status == ATTACK_JMP || status == BEING_HIT_2) {
		height -= (int)verticalForce;
		position.x += (int)horizontalForce;
		if (height < 0) {
			height = 0;
			verticalForce = 0.0f;
		}
		position.y += (int)verticalForce;
	}
	if (depth > 53) {
		position.y = 102;
		depth = 53;
	}
	if (depth < 0 || position.y > 155) {
		position.y = 155;
		depth = 0;
	}
	if (status == IDLE || status == WALK)
		position.y = 155 - depth - height;
}*/

/*void Enemy::paint()
{
	// Update colliders in here (in order to use the same SDL_Rect as Blit)
	bool flip = false;
	Frame currentFrame = current_animation->GetCurrentFrame();
	int offset = currentFrame.offset;

	if (facing == LEFT) {
		flip = true;
		offset = currentFrame.rect.w - idle.frames.front().rect.w - offset;
	}
	App->renderer->Blit(graphics, position.x - offset, position.y, &(currentFrame.rect), flip);
	if (baseCollider != nullptr) {
		baseCollider->rect = currentFrame.rect;
		baseCollider->SetPos(position.x - offset, position.y);
	}
}*/