#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneLevel.h"
#include "ModuleEnemy.h"


ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading space scene");

	background = App->textures->Load("TMNT/stage.png");

	App->player->Enable();
	App->enemy->Enable();
	App->particles->Enable();
	App->collision->Enable();


	App->audio->PlayMusic("TMNT/stage1.ogg", 1.0f);

/*
	iPoint posEnemy;
	posEnemy.x = 60;
	posEnemy.y = 100;
	App->enemy->AddEnemy(App->enemy->enemy1, posEnemy, Enemy::PURPLE);*/

	App->collision->AddCollider({ 0,0,1350, 130 }, COLLIDER_WALL, this);

	App->collision->AddCollider({ 0,SCREEN_HEIGHT,1350, 2 }, COLLIDER_WALL, this);


	App->particles->AddParticle(App->particles->fire1, 0, 157, 0,  COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 0, 168, 0,  COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire1, 301, 157, 0,  COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 301, 168, 0,  COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire1, 602, 157, 0,  COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 602, 168, 0,  COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire1, 903, 157, 0,  COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 903, 168, 0,  COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire1, 1204, 157, 0,  COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 1204, 168, 0, COLLIDER_NONE);


	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->enemy->Enable();
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update()
{
	// Move camera forward -----------------------------
	int scroll_speed = 1;

	//App->player->position.x += 1;
	//App->renderer->camera.x -= 3;

	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);

	return UPDATE_CONTINUE;
}