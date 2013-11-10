#if !defined (CURSOR_RESOURCE)
#define CURSOR_RESOURCE

#include "GameResource.h"

class GameManager;

class CursorResource : public GameResource
{
   private:
      GameManager* game_manager;

   public:
      CursorResource(unsigned int id, std::string group_name, std::string file_name, GameResourceType type, GameManager* gm);
      virtual ~CursorResource();

      virtual void load();
      virtual void unload();
};

#endif