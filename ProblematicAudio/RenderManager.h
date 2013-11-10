#if !defined (RENDER_MANAGER)
#define RENDER_MANAGER
#include "Ogre.h"
#include "RenderListener.h"
#include <iostream>
#include "TinyXML.h"
#include "TransformType.h"
#include "GUIManager.h"

class GameManager;

class RenderManager : public Ogre::RenderQueueListener, public Ogre::WindowEventListener, public Ogre::Viewport::Listener
{
   private:
      Ogre::Root* root;
      Ogre::RenderWindow* window;
      Ogre::SceneManager* scene_manager;

      Ogre::Camera* camera;
      Ogre::Viewport* viewport;

      RenderListener* render_listener;
      Ogre::Real time_since_last_frame;
	  
      GameManager* game_manager;
	  GUIManager* gui_manager;  //Rocket
	  
	  //std::string current_group ="";

     // void init();

      size_t window_handle;
	  
	  bool rocket_enabled;

      //void addSceneNodeChildren(TiXmlNode* xml_node, Ogre::SceneNode* parent_node);

	  void buildChildren(TiXmlNode* childrens_tree, Ogre::SceneNode* parent_node);
	  void buildEntityNode(TiXmlNode* entity_node, Ogre::SceneNode* sNode);
	  void buildAnimationNode(TiXmlNode* animation_node, Ogre::SceneNode* sNode);
	  		
      void buildSubmarineSceneGraph();
      //void buildSubmarineAnimation(Ogre::SceneNode* scene_node);
      //void buildPropellerAnimation(Ogre::SceneNode* scene_node);
      //void buildPeriscopeAnimation(Ogre::SceneNode* scene_node);
      //void buildRudderAnimation(Ogre::SceneNode* scene_node);

   public:
   
   /*******WindowEventListener***********/
   void windowMoved(Ogre::RenderWindow *rw) {} ;
   void windowResized(Ogre::RenderWindow *rw);
   bool windowClosing(Ogre::RenderWindow *rw);
   void windowClosed(Ogre::RenderWindow *rw){};
   void windowFocusChange(Ogre::RenderWindow *rw) {};
   /****************************************/
   
   /**********ViewportListener**************/
   void viewportCameraChanged(Ogre::Viewport *vp) {};
   void viewportDimensionsChanged(Ogre::Viewport *vp);
   void viewportDestroyed(Ogre::Viewport* vp){};
   /****************************************/
   
      RenderManager(GameManager* game_manager);
      virtual ~RenderManager();

	   void initOgre();

      void loadResourceGroup(std::string section_name);
      void unloadResourceGroup(std::string group_name);
      void initialiseResourceGroup(std::string group_name);
	  
   //   void loadOgreResources(std::string section_name);
   //   void unloadOgreResources(std::string group_name);

      void buildSceneFromXML(std::string file_name);

      int getWindowWidth();
      int getWindowHeight();
      size_t getWindowHandle();

      void startRendering();
      void stopRendering();
	  
      void checkInput();
	  void updateAudio();

      void updateCameraRotation(float yaw, float pitch);
      void updateCameraPosition(float x, float y, float z);
	  
	  void toggleLightSource(std::string light_name);
	  void turnLightSourceOn(std::string light_name);
	  void turnLightSourceOff(std::string light_name);
	  
	  void resetTransformNode(std::string node_name);  //Useless
	  void updateTransformNode(std::string transform_node_name, TransformType transform, double xVal, double yVal, double zVal, double qVal = 0); //Default value for q, since will only be used for TransformType ROTATE

      //void updateSceneNodeRotation(std::string scene_node_name, float _yaw, float _pitch, float _roll);
      void setTimeSinceLastFrame(Ogre::Real tslf);
	  
	  void addPathResource(std::string file_name, std::string path_type, std::string group_name);
      void addMeshResource(std::string file_name, std::string mesh_str, std::string group_name);
	  
	  //pass through methods to the gui manager
      void loadRocket(std::string current_group);
      void unloadRocket();

      void loadRocketCursor(std::string cursor_file_name, std::string group_name);
      void loadRocketDocument(std::string doc_file_name, std::string group_name);
      void loadRocketFont(std::string font_file_name, std::string group_name);

      void rocketMouseMoved(float x_abs, float y_abs);
      void rocketMousePressed(int mouse_x, int mouse_y, int button_id);
      void rocketMouseReleased(int mouse_x, int mouse_y, int button_id);

      void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation));
      void renderQueueEnded(Ogre::uint8 ROCKET_UNUSED(queueGroupId), const Ogre::String& ROCKET_UNUSED(invocation), bool& ROCKET_UNUSED(repeatThisInvocation));

      void enableRocket();
      bool isRocketEnabled();
	
	  
};

#endif
