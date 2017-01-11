#ifndef __MODULESCENELEVEL_H__
#define __MODULESCENELEVEL_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneLevel : public Module
{
public:
	ModuleSceneLevel(bool active = true);
	~ModuleSceneLevel();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
};

#endif /