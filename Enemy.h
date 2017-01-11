#ifndef __Enemy_H__
#define __Enemy_H__

#include "Timer.h"
#include "Entity.h"
#include "Animation.h"


class Enemy : public Entity {
public:
	enum State
	{
		RESPAWNING,
		IDLE,
		WALKRIGTH,
		WALKUP,
		JUMP_INI,
		JUMPING,
		JUMP_END,
		ATTACK_JMP,
		ATTACKING,
		ATTACKING_2,
		ATTACKING_3,
		ATTACKING_4,
		BEING_HIT,
		BEING_HIT_2_INI,
		BEING_HIT_2,
		BEING_HIT_2_END,
		KNOCKED,
		DEAD,
		UNKNOWN
	};
	enum Direction
	{
		LEFT,
		RIGHT
	};
	enum EnemyType
	{
		PURPLE,
		ORANGE
	};

	Enemy(EntityType entityType);
	Enemy();
	virtual ~Enemy();
	virtual bool Start();
	virtual update_status Update();
	virtual bool Update2();
	//virtual void updatePosition();
	void setCurrentAnimation(Animation* anim);
	//void handleState();
	bool isAttacking() const;
	bool canBeAttacked() const;
	//virtual void paint();
	virtual void spawn();
	//void hit(Entity* c2);
public:
	Animation* current_animation = nullptr;
	Animation idle;
	Animation up;
	Animation upLeft;
	Animation waiting;
//	Animation walkingRight;
	Animation walkingLeft;
	Animation jumping;
	Animation jumpKick;
	Animation attack1;
	Animation attack2;
	Animation attack1Left;
	Animation attack2Left;
	Animation chop;
	Animation kick;
	Animation respawning;
	Animation beingHit;
	Animation beingHit2;
	Animation beingHit3;
	Animation beingHit4;
	Animation beingHit5;
	Animation beingHit6;
	Animation gettingUp;
	Animation knockedOut;
	iPoint velocity = { 0, 0 };
	iPoint prevVelocity = { 0, 0};
	 int cont = 0;
	unsigned short int consecutiveHits = 0;
	float verticalForce = 0.0f;
	float horizontalForce = 0.0f;
	bool attacking = false;
	bool jumped = false;
	bool dead = false;
	EnemyType enemyType = PURPLE;
	State status = UNKNOWN;
	SimpleTimer EnemyTimer, refreshTimer, movementTimer, jumpTimer;
	SimpleTimer hitTimer, attackTimer, beingHitTimer;
	Collider* attackCollider = nullptr;
	Collider* feetCollider = nullptr;
	Direction facing = LEFT;



};

#endif 