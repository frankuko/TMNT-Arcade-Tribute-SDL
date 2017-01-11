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


	iPoint posEnemy;
	posEnemy.x = 150;
	posEnemy.y = 160;
	App->enemy->AddEnemy(App->enemy->enemy1, posEnemy, Enemy::PURPLE);

	App->collision->AddCollider({ 0,0,1350, 130 }, COLLIDER_WALL, this);

	App->collision->AddCollider({ 0,SCREEN_HEIGHT,1350, 2 }, COLLIDER_WALL, this);

	//168
	App->particles->AddParticle(App->particles->fire2, 0, 190, 0,  COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 0, 200, 0,  COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 0, 180, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 0, 170, 0, COLLIDER_NONE);


	App->particles->AddParticle(App->particles->fire2, 300, 190, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 300, 200, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 300, 180, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 300, 170, 0, COLLIDER_NONE);


	App->particles->AddParticle(App->particles->fire2, 600, 190, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 600, 200, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 600, 180, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 600, 170, 0, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire2, 900, 190, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 900, 200, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 900, 180, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 900, 170, 0, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire2, 1200, 190, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 1200, 200, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire1, 1200, 180, 0, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 1200, 170, 0, COLLIDER_NONE);


	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);
	App->player->Disable();
	App->enemy->Disable();
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