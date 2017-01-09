#ifndef __Timer_H__
#define __Timer_H__

#include "SDL\include\SDL.h"

class SimpleTimer
{
public:
	SimpleTimer()
		: start(SDL_GetTicks())
	{}
	Uint32 getDelta() const {
		return SDL_GetTicks() - start;
	}
	void reset()
	{
		start = SDL_GetTicks();
	}
public:
	Uint32 start;
};

#endif