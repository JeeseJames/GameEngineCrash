#include "DocumentResource.h"
#include "GameManager.h"

DocumentResource::DocumentResource(unsigned int id, std::string group_name, std::string path, GameResourceType type, GameManager* gm) : GameResource(id, group_name, path, type)
{
   game_manager = gm;
}

DocumentResource::~DocumentResource()
{
   game_manager = NULL;
}

void DocumentResource::load()
{
   game_manager->loadRocketDocument(getResourceFileName(), getResourceGroupName());
}

void DocumentResource::unload()
{}