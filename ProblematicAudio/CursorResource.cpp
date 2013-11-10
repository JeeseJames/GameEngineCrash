#include "CursorResource.h"
#include "GameManager.h"

CursorResource::CursorResource(unsigned int id, std::string group_name, std::string path, GameResourceType type, GameManager* gm) : GameResource(id, group_name, path, type)
{
   game_manager = gm;
}

CursorResource::~CursorResource()
{
   game_manager = NULL;
}

void CursorResource::load()
{
   game_manager->loadRocketCursor(getResourceFileName(), getResourceGroupName());
}

void CursorResource::unload()
{}