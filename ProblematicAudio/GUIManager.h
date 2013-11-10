#if !defined (GUI_MANAGER)
#define GUI_MANAGER

#include <iostream>

#include "Rocket/Core.h"
#include "SystemInterfaceOgre3D.h"
#include "RenderInterfaceOgre3D.h"

class RenderManager;

class GUIManager
{
   private:
      Rocket::Core::Context* rocket_context;
      SystemInterfaceOgre3D* rocket_ogre_system;
      RenderInterfaceOgre3D* rocket_ogre_renderer;
      RenderManager* render_manager;

   public:
      GUIManager(RenderManager* render_manager);
      virtual ~GUIManager();

      void loadRocket(std::string current_group, int window_width, int window_height);
      void unloadRocket();
      void renderQueueStarted(int window_width, int window_height);

      void rocketMouseMoved(float x_abs, float y_abs);
      void rocketMousePressed(int mouse_x, int mouse_y, int button_id);
      void rocketMouseReleased(int mouse_x, int mouse_y, int button_id);

      void loadRocketCursor(std::string cursor_file_name, std::string group_name);
      void loadRocketDocument(std::string doc_file_name, std::string group_name);
      void loadRocketFont(std::string font_file_name, std::string group_name);

      void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& ROCKET_UNUSED(skipThisInvocation));
      void renderQueueEnded(Ogre::uint8 ROCKET_UNUSED(queueGroupId), const Ogre::String& ROCKET_UNUSED(invocation), bool& ROCKET_UNUSED(repeatThisInvocation));
	
	  void windowResized(int window_width, int window_height);
	  
};

#endif
