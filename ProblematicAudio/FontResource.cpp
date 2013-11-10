#include "FontResource.h"
#include "GameManager.h"

FontResource::FontResource(unsigned int id, std::string group_name, std::string path, GameResourceType type, GameManager* gm) : GameResource(id, group_name, path, type)
{
   game_manager = gm;
}

FontResource::~FontResource()
{
   game_manager = NULL;
}

void FontResource::load()
{
   game_manager->loadRocketFont(getResourceFileName(), getResourceGroupName());
}

void FontResource::unload()
{}