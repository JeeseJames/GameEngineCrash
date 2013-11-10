#if !defined (DOCUMENT_RESOURCE)
#define DOCUMENT_RESOURCE

#include "GameResource.h"

class GameManager;

class DocumentResource : public GameResource
{
   private:
      GameManager* game_manager;

   public:
      DocumentResource(unsigned int id, std::string group_name, std::string file_name, GameResourceType type, GameManager* gm);
      virtual ~DocumentResource();

      virtual void load();
      virtual void unload();
};

#endif