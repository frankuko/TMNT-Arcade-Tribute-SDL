#include <iostream>

#include "PlayerStateMachine.h"


//-----------------------------------------------------------------------------------------
// Update of the StateMachine. 
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::Update()
{
	StateMachine::Update();
}

//-----------------------------------------------------------------------------------------
// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
/*void PlayerStateMachine::HealthPotion()
{
	BEGIN_TRANSITION_MAP                      // - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)   // ST_Undefined
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Healthy
		TRANSITION_MAP_ENTRY(ST_HEALTHY)     // ST_Damaged
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Dead
	END_TRANSITION_MAP(NULL)
}*/

//-----------------------------------------------------------------------------------------
// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::ReceiveDamage()
{
	BEGIN_TRANSITION_MAP                      // - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)   // ST_Undefined
		TRANSITION_MAP_ENTRY(ST_DAMAGED)     // ST_Healthy
		TRANSITION_MAP_ENTRY(ST_DEAD)        // ST_Damaged
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Dead
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Attacking
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Jumping
	END_TRANSITION_MAP(NULL)
}

// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::Jump()
{
	BEGIN_TRANSITION_MAP                      // - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)   // ST_Undefined
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Healthy
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Damaged
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Dead
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Attacking
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Jumping
	END_TRANSITION_MAP(NULL)
}

// Event happened. It makes the transition to the corresponding state.
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::Attack()
{
	BEGIN_TRANSITION_MAP                      // - Current State -
		TRANSITION_MAP_ENTRY(ST_UNDEFINED)   // ST_Undefined
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Healthy
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Damaged
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Dead
		TRANSITION_MAP_ENTRY(ST_ATTACKING)  // ST_Attacking
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)  // ST_Jumping
	END_TRANSITION_MAP(NULL)
}


//-----------------------------------------------------------------------------------------
// Converts a State type to a string
//-----------------------------------------------------------------------------------------
const char * PlayerStateMachine::StateToStr(State state)
{
	const char *paszStates[] = {
#define PLAYER_STATE(_state, _func) #_state,
#include "PlayerState.h"
#undef PLAYER_STATE
	};
	return paszStates[state];
}


//-----------------------------------------------------------------------------------------
// Undefined State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Undefined(State PrevState, const EventData* pData)
{
	std::cout << "OnEnter_Undefined. PrevState: " << StateToStr(PrevState) << "\n";
	OnEvent(ST_HEALTHY, NULL);
}

void PlayerStateMachine::OnUpdate_Undefined()
{
	std::cout << "OnUpdate_Undefined\n";
	OnEvent(ST_HEALTHY, NULL);
}

void PlayerStateMachine::OnExit_Undefined(State NextState)
{
	std::cout << "OnExit_Undefined. NextState: " << StateToStr(NextState) << "\n";
}

//-----------------------------------------------------------------------------------------
// Healthy State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Healthy(State PrevState, const EventData* pData)
{
	std::cout << "OnEnter_Healthy. PrevState: " << StateToStr(PrevState) << "\n";
}

void PlayerStateMachine::OnUpdate_Healthy()
{
	std::cout << "OnUpdate_Healthy\n";
}

void PlayerStateMachine::OnExit_Healthy(State NextState)
{
	std::cout << "OnExit_Healthy. NextState: " << StateToStr(NextState) << "\n";
}

//-----------------------------------------------------------------------------------------
// Damaged State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Damaged(State PrevState, const EventData* pData)
{
	std::cout << "OnEnter_Damaged. PrevState: " << StateToStr(PrevState) << "\n";
}

void PlayerStateMachine::OnUpdate_Damaged()
{
	std::cout << "OnUpdate_Damaged\n";
}

void PlayerStateMachine::OnExit_Damaged(State NextState)
{
	std::cout << "OnExit_Damaged. NextState: " << StateToStr(NextState) << "\n";
}

//-----------------------------------------------------------------------------------------
// Dead State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Dead(State PrevState, const EventData* pData)
{
	std::cout << "OnEnter_Dead. PrevState: " << StateToStr(PrevState) << "\n";
}

void PlayerStateMachine::OnUpdate_Dead()
{
	std::cout << "OnUpdate_Dead\n";
}

void PlayerStateMachine::OnExit_Dead(State NextState)
{
	std::cout << "OnExit_Dead. NextState: " << StateToStr(NextState) << "\n";
}

//-----------------------------------------------------------------------------------------
// Attacking State
//-----------------------------------------------------------------------------------------
void PlayerStateMachine::OnEnter_Attacking(State PrevState, const EventData* pData)
{
	std::cout << "OnEnter_Attacking. PrevState: " << StateToStr(PrevState) << "\n";

	
}

void PlayerStateMachine::OnUpdate_Attacking()
{
	std::cout << "OnUpdate_Attacking\n";
}

void PlayerStateMachine::OnExit_Attacking(State NextState)
{
	std::cout << "OnExit_Attacking. NextState: " << StateToStr(NextState) << "\n";
}


//-----------------------------------------------------------------------------------------
// Jumping State
//-----------------------------------------------------------------------------------------

void PlayerStateMachine::OnEnter_Jumping(State PrevState, const EventData* pData)
{
	std::cout << "OnEnter_Jumping. PrevState: " << StateToStr(PrevState) << "\n";
}

void PlayerStateMachine::OnUpdate_Jumping()
{
	std::cout << "OnUpdate_Jumping\n";
}

void PlayerStateMachine::OnExit_Jumping(State NextState)
{
	std::cout << "OnExit_Jumping. NextState: " << StateToStr(NextState) << "\n";
}