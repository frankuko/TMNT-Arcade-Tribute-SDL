#include "Entity.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"

Entity::Entity(EntityType entityType)
	:entityType(entityType)
{
}

Entity::~Entity()
{}


bool Entity::Start()
{
	return true;
}

update_status Entity::Update()
{
	return UPDATE_CONTINUE;
}

bool Entity::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}

bool Entity::isCreature() const {
	return (entityType == PLAYER || entityType == ENEMY);
}