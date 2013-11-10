#if !defined (FONT_RESOURCE)
#define FONT_RESOURCE

#include "GameResource.h"

class GameManager;

class FontResource : public GameResource
{
   private:
      GameManager* game_manager;

   public:
      FontResource(unsigned int id, std::string group_name, std::string file_name, GameResourceType type, GameManager* gm);
      virtual ~FontResource();

      virtual void load();
      virtual void unload();
};

#endif