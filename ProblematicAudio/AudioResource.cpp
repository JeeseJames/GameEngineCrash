#include "AudioResource.h"
#include "GameManager.h"
using namespace std;

AudioResource::AudioResource(unsigned int id, std::string scope, std::string file_name, GameResourceType type, AudioType audio_type, GameManager* gm) : GameResource(id, scope, file_name, type)
{
   game_manager = gm;
   this->audio_type = audio_type;
   ar_info = game_manager->createAudioResourceInfo();
}

AudioResource::~AudioResource()
{
   unload();
   free(ar_info);
   game_manager = NULL;
}

AudioResourceInfo* AudioResource::getAudioResourceInfo()
{
   return ar_info;
}

//should probably be in a try-catch block in case the file cannot be found
//such a failure should not terminate the game, however
void AudioResource::load()
{
//cout<<"14 characters";
   if (audio_type == SAMPLE)
   {
      game_manager->loadSampleAudioResource(getResourceFileName(), ar_info);
   }
   else 
   {
      game_manager->loadStreamAudioResource(getResourceFileName(), ar_info);
   }
}

void AudioResource::unload()
{
   if (audio_type == SAMPLE)
   {
      game_manager->unloadSampleAudioResource(ar_info);
   }
   else 
   {
      game_manager->unloadStreamAudioResource(ar_info);
   }
}
