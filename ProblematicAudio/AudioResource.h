#if !defined (AUDIO_RESOURCE)
#define AUDIO_RESOURCE

#include "GameResource.h"
#include "AudioType.h"
#include <iostream>

class GameManager;
struct AudioResourceInfo;

class AudioResource : public GameResource
{
   private:
      AudioResourceInfo* ar_info;
      AudioType audio_type;
      GameManager* game_manager;

   public:
      AudioResource(unsigned int id, std::string scope, std::string file_name, GameResourceType type, AudioType audio_type, GameManager* gm);
      virtual ~AudioResource();

      virtual void load();
      virtual void unload();

      AudioResourceInfo* getAudioResourceInfo();
};

#endif