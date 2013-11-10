#if !defined (GAME_MANAGER)
#define GAME_MANAGER

#include "ErrorLogManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "BehaviorManager.h"

#include "TinyXML.h"

//supplies communication between managers
class GameManager 
{
   private:
      ErrorLogManager* error_log_manager;  //must use this variable name for macros in ErrorLogManager
      RenderManager* render_manager;
      InputManager* input_manager;
      ResourceManager* resource_manager;
	  AudioManager* audio_manager;
	  BehaviorManager* behavior_manager;

      GameManager();
      void init();


   public:
      virtual ~GameManager();
      static GameManager* getGameManager();

      int getWindowWidth();
      int getWindowHeight();
      size_t getWindowHandle();
	  
	  //propagates to render manager
	  void stopRendering();
	  void updateCameraPosition(float x, float y, float z);
	  void updateCameraRotation(float yaw, float pitch);
	  void updateTransformNode(std::string transform_node_name, TransformType transform, double xVal, double yVal, double zVal, double qVal = 0); //Default value for q, since will only be used for TransformType ROTATE;
      void toggleLightSource(std::string light_name);
	  void turnLightSourceOn(std::string light_name);
	  void turnLightSourceOff(std::string light_name);
	  void resetTransformNode(std::string node_name);


      void checkInput();
	  void updateAudio();

      static double parseDouble(std::string& str);
      static double* parseDoubles(std::string& str);
      static std::string textFromChildNode(TiXmlNode* parent_node, const char* child_element_name);
      void loadBehaviorsFromXML(std::string file_name);

 //     void addResourceLocation(std::string file_name, std::string path_type, std::string group_name);
 //     void declareResource(std::string file_name, std::string, std::string group_name);
 //     void unloadOgreResources(std::string group_name);
 //     void loadOgreResources(std::string group_name);
	  
	  void addPathResource(std::string file_name, std::string path_type, std::string group_name);
      void addMeshResource(std::string file_name, std::string, std::string group_name);

      void initialiseRenderResourceGroup(std::string group_name);
      void loadRenderResourceGroup(std::string group_name);
      void unloadRenderResourceGroup(std::string group_name);
	  
	  void logException(std::string exception_message);
      void logProgress(std::string progress_message);
	  
	  void loadSampleAudioResource(std::string file_name, AudioResourceInfo* ar_info);
      void loadStreamAudioResource(std::string file_name, AudioResourceInfo* ar_info);
      void unloadSampleAudioResource(AudioResourceInfo* ar_info);
      void unloadStreamAudioResource(AudioResourceInfo* ar_info);
	  
      void loadRocketFont(std::string file_name, std::string group_name);
      void loadRocketCursor(std::string file_name, std::string group_name);
      void loadRocketDocument(std::string file_name, std::string group_name);
	  
	  void loadRocket(std::string current_group);
      void unloadRocket();
      void enableRocket();
      bool isRocketEnabled();
	  
	  void playAudio(int id, int num_plays);
	  
	  AudioResourceInfo* createAudioResourceInfo();

      void rocketMouseMoved(int mouse_x_abs, int mouse_y_abs);
      void rocketMousePressed(int mouse_x_abs, int mouse_y_abs, int game_mouse);
      void rocketMouseReleased(int mouse_x_abs, int mouse_y_abs, int game_mouse);
	  

};

#endif