#include "AudioManager.h"
#include "AudioResource.h"
#include "GameManager.h"
#include <iostream>
using namespace std;

AudioResourceInfo* AudioManager::createAudioResourceInfo()
{
   AudioResourceInfo* ar_info = (AudioResourceInfo*) malloc(sizeof(AudioResourceInfo));
   ar_info->sample_data = 0;
   ar_info->channel_data = 0;
   ar_info->loaded = false;
   return ar_info;
}

void AudioManager::unloadSampleAudioResource(AudioResourceInfo* ar_info)
{
   if (!ar_info->loaded) return;

   BASS_SampleFree(ar_info->sample_data);
   ar_info->sample_data = 0;
   ar_info->channel_data = 0;
   ar_info->loaded = false;
}

void AudioManager::unloadStreamAudioResource(AudioResourceInfo* ar_info)
{
   if (!ar_info->loaded) return;

   BASS_StreamFree(ar_info->stream_data);
   ar_info->stream_data = 0;
   ar_info->channel_data = 0;
   ar_info->loaded = false;
}

void AudioManager::loadSampleAudioResource(std::string file_name, AudioResourceInfo* ar_info)
{
   ar_info->sample_data = BASS_SampleLoad(FALSE, file_name.c_str(),0,0,1,0);
   if (ar_info->sample_data)
   {
      ar_info->channel_data = BASS_SampleGetChannel(ar_info->sample_data, false);
      ar_info->loaded = true;
   }
   else
   {
      game_manager->logException("Sample Audio Resource Initialization Error: " + file_name);
   }
}

void AudioManager::loadStreamAudioResource(std::string file_name, AudioResourceInfo* ar_info)
{
   ar_info->stream_data = BASS_StreamCreateFile(FALSE, file_name.c_str(),0,0,0);
   if (ar_info->stream_data)
   {
      ar_info->channel_data = ar_info->stream_data;
      ar_info->loaded = true;
   }
   else
   {
      game_manager->logException("Stream Audio Resource Initialization Error: " + file_name);
   }
}

AudioManager::AudioManager(GameManager* gm)
{
   game_manager = gm;
   audio_players = new ListArray<AudioPlayer>();
   init();
}

AudioManager::~AudioManager()
{
   free();

   ListArrayIterator<AudioPlayer>* iter = audio_players->iterator();
   while(iter->hasNext())
   {
      AudioPlayer* ap = iter->next();
      delete ap;
   }

   delete iter;
   delete audio_players;
}

void AudioManager::init(int Device, DWORD SampleRate, DWORD flags, HWND win)
{
   BOOL bassActive = BASS_Init(Device, SampleRate, flags, win, NULL);
   if (!bassActive)
   {
      THROW_EXCEPTION(1, "Audio Manager Initialization Problem");
   }

   std::stringstream DeviceStringStream;
   if (BASS_GetDeviceInfo(Device, &device_info))
   {
      DeviceStringStream << "Audio Device Info. Name: " << device_info.name << "Driver: " << device_info.driver;
      device_info_str = DeviceStringStream.str();
std::cout << device_info_str << std::endl;
   }

   else
   {
      BASS_Free();  //clean up before throwing the exception
      THROW_EXCEPTION(1, "Audio Manager Initialization Problem");
   }
}

void AudioManager::free()
{
   BASS_Free();
}

void AudioManager::playAudio(AudioResource* ar, int num_repeats)
{
   AudioPlayer* ap = new AudioPlayer(ar, num_repeats);
   addAudioPlayer(ap);
}

void AudioManager::addAudioPlayer(AudioPlayer* audio_player)
{
   audio_players->add(audio_player);

   AudioResource* audio_resource = audio_player->getAudioResource();
   AudioResourceInfo* ar_info = audio_resource->getAudioResourceInfo();
   BASS_ChannelPlay(ar_info->channel_data, false);
}

void AudioManager::updateAudio()
{
   int num_players = audio_players->size();

   for (int i = 1; i <= num_players; i++)
   {
      AudioPlayer* audio_player = audio_players->get(i);
      AudioResource* audio_resource = audio_player->getAudioResource();
      AudioResourceInfo* ar_info = audio_resource->getAudioResourceInfo();

      //has the sound completed playing?  if so, repeat if required or remove it from the list
      if (BASS_ChannelIsActive(ar_info->channel_data) == BASS_ACTIVE_STOPPED)
      {
         //a num_repeat of zero means play once, repeat_count is initialized to zero
         if (audio_player->getRepeatCount() >= audio_player->getNumRepeats())  //tricky
         {
            audio_players->remove(i);
            audio_player->onMediaComplete();  //eventually, notify listeners that the audio has completed
            i--;
            num_players--;
         }

         else
         {
            audio_player->incRepeatCount();
            BASS_ChannelPlay(ar_info->channel_data, false);
         }
      }
   }
}
