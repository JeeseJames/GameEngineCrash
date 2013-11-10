#include "GUIManager.h"
#include "RenderManager.h"
#include "ErrorLogManager.h"

#include "Rocket/Controls.h"

//using namespace Ogre;
using namespace std;

void GUIManager::renderQueueStarted(int window_width, int window_height)
{
   rocket_context->Update();  //updates input
   rocket_ogre_renderer->configureRenderSystem(window_width, window_height);
   rocket_context->Render();  //adds to the render queue
}

void GUIManager::rocketMouseMoved(float x_abs, float y_abs)
{
   rocket_context->ProcessMouseMove(x_abs, y_abs, 0);
}

void GUIManager::rocketMousePressed(int mouse_x, int mouse_y, int button_id)
{
   //allows the GUI to be moved around
   rocket_context->ProcessMouseButtonDown(button_id, 0);
}

void GUIManager::rocketMouseReleased(int mouse_x, int mouse_y, int button_id)
{
   //allows the GUI to be moved around
   rocket_context->ProcessMouseButtonUp(button_id, 0);
}

GUIManager::GUIManager(RenderManager* rm)
{
   render_manager = rm;

   rocket_context = NULL;
   rocket_ogre_system = NULL;
   rocket_ogre_renderer = NULL;
}

GUIManager::~GUIManager()
{
   //should have already been unloaded
}

void GUIManager::loadRocketFont(std::string font_file_name, std::string group_name)
{
   Rocket::Core::FontDatabase::LoadFontFace(font_file_name.c_str());
}

void GUIManager::loadRocketCursor(std::string cursor_file_name, std::string group_name)
{
   Rocket::Core::ElementDocument* cursor = rocket_context->LoadMouseCursor(cursor_file_name.c_str());
   if (cursor)
   {
      cursor->RemoveReference();  //makes reference counting work
   }
}

void GUIManager::loadRocketDocument(std::string doc_file_name, std::string group_name)
{
   Rocket::Core::ElementDocument* document = rocket_context->LoadDocument(doc_file_name.c_str());
   if (document)
   {
      document->Show();
      document->RemoveReference();
   }
}

void GUIManager::loadRocket(std::string current_group, int window_width, int window_height)
{
   rocket_ogre_renderer = new RenderInterfaceOgre3D(window_width, window_height, current_group);
   Rocket::Core::SetRenderInterface(rocket_ogre_renderer);
   rocket_ogre_system = new SystemInterfaceOgre3D();
   Rocket::Core::SetSystemInterface(rocket_ogre_system);

   Rocket::Core::Initialise();
   Rocket::Controls::Initialise();

   rocket_context = Rocket::Core::CreateContext("main", Rocket::Core::Vector2i(window_width, window_height));
   //Rocket::Debugger::Initialise(rocket_context);
}

void GUIManager::windowResized(int window_width, int window_height)
{
	//rocket_ogre_renderer->configureRenderSystem(window_width, window_height);
	rocket_context->SetDimensions(Rocket::Core::Vector2i(window_width, window_height));
	rocket_context->Update();
}

void GUIManager::unloadRocket()
{
   rocket_context->RemoveReference();
   Rocket::Core::Shutdown();

   delete rocket_ogre_system;
   rocket_ogre_system = NULL;

   delete rocket_ogre_renderer;
   rocket_ogre_renderer = NULL;
}
