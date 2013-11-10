#include "GameManager.h"
#include "CSC2110/String.h"

#include <stdlib.h>
#include <iostream>
using namespace std;



bool GameManager::isRocketEnabled()
{
   return render_manager->isRocketEnabled();
}

void GameManager::enableRocket()
{
   render_manager->enableRocket();
}

void GameManager::loadRocket(std::string current_group)
{
   render_manager->loadRocket(current_group);
}

void GameManager::unloadRocket()
{
   render_manager->unloadRocket();
}

void GameManager::rocketMouseMoved(int mouse_x_abs, int mouse_y_abs)
{
   render_manager->rocketMouseMoved(mouse_x_abs, mouse_y_abs);
}

void GameManager::rocketMousePressed(int mouse_x_abs, int mouse_y_abs, int game_mouse)
{

  render_manager->rocketMousePressed(mouse_x_abs, mouse_y_abs, game_mouse);
}

void GameManager::rocketMouseReleased(int mouse_x_abs, int mouse_y_abs, int game_mouse)
{
   render_manager->rocketMouseReleased(mouse_x_abs, mouse_y_abs, game_mouse);
}

void GameManager::playAudio(int id, int num_plays)
{
   AudioResource* ar = (AudioResource*) resource_manager->findResourceByID(id);
   audio_manager->playAudio(ar, num_plays);
}

void GameManager::updateAudio()
{
   audio_manager->updateAudio();
}

AudioResourceInfo* GameManager::createAudioResourceInfo()
{
   return audio_manager->createAudioResourceInfo();
}

void GameManager::loadRocketDocument(std::string file_name, std::string group_name)
{
   render_manager->loadRocketDocument(file_name, group_name);
}

void GameManager::loadRocketCursor(std::string file_name, std::string group_name)
{
   render_manager->loadRocketCursor(file_name, group_name);
}

void GameManager::loadRocketFont(std::string file_name, std::string group_name)
{
   render_manager->loadRocketFont(file_name, group_name);
}

void GameManager::loadSampleAudioResource(std::string file_name, AudioResourceInfo* ar_info)
{
   audio_manager->loadSampleAudioResource(file_name, ar_info);
}

void GameManager::loadStreamAudioResource(std::string file_name, AudioResourceInfo* ar_info)
{
   audio_manager->loadStreamAudioResource(file_name, ar_info);
}

void GameManager::unloadSampleAudioResource(AudioResourceInfo* ar_info)
{
   audio_manager->unloadSampleAudioResource(ar_info);
}

void GameManager::unloadStreamAudioResource(AudioResourceInfo* ar_info)
{
   audio_manager->unloadStreamAudioResource(ar_info);
} 

void GameManager::logException(std::string exception_message)
{
   error_log_manager->logException(exception_message);
}

void GameManager::logProgress(std::string progress_message)
{
   error_log_manager->logProgress(progress_message);
}

void GameManager::initialiseRenderResourceGroup(std::string group_name)
{
   render_manager->initialiseResourceGroup(group_name);
}

void GameManager::loadRenderResourceGroup(std::string group_name)
{
   render_manager->loadResourceGroup(group_name);
}

void GameManager::unloadRenderResourceGroup(std::string group_name)
{
   render_manager->unloadResourceGroup(group_name);
}

void GameManager::addPathResource(std::string file_name, std::string path_type, std::string group_name)
{
   render_manager->addPathResource(file_name, path_type, group_name);
}
      
void GameManager::addMeshResource(std::string file_name, std::string mesh_str, std::string group_name)
{
   render_manager->addMeshResource(file_name, mesh_str, group_name);
}
/*

void GameManager::loadOgreResources(std::string group_name)
{
   render_manager->loadOgreResources(group_name);
}

void GameManager::unloadOgreResources(std::string group_name)
{
   render_manager->unloadOgreResources(group_name);
}

void GameManager::addResourceLocation(std::string file_name, std::string path_type, std::string group_name)
{
   render_manager->addResourceLocation(file_name, path_type, group_name);
}
      
void GameManager::declareResource(std::string file_name, std::string mesh_str, std::string group_name)
{
   render_manager->declareResource(file_name, mesh_str, group_name);
}
*/
//the problem is that in C++, it is not known when this initialization code will be called
//so we will use a function static variable that is initialized the first time the method is called
GameManager* GameManager::getGameManager()
{
   static GameManager game_manager;  //initialized when method is called the first time
   return &game_manager;  //won't go out of scope as game_manager is static
}

GameManager::GameManager()
{
   error_log_manager = new ErrorLogManager("GameLog.txt");
   init();
   render_manager->startRendering();
}

GameManager::~GameManager()
{
   delete input_manager;
   resource_manager->unloadResources();

   delete render_manager;
   delete resource_manager;
   delete error_log_manager;

   
}

void GameManager::checkInput()
{
   input_manager->checkInput();
   behavior_manager->checkInput(); //Checks for Held Behaviors
}

void GameManager::init()
{
   try
   {
      render_manager = new RenderManager(this);  //careful: "this" must be valid
	  render_manager->initOgre();
      resource_manager = new ResourceManager(this);
	  audio_manager = new AudioManager(this);
	  
      resource_manager->loadFromXMLFile("resources.xml");
      resource_manager->loadResources("default");
      render_manager->buildSceneFromXML("scene.xml");  

      input_manager = new InputManager(this);  //this instruction must come after the render_manager has been initialized (for the window handle)
      behavior_manager = new BehaviorManager(this);
	  input_manager->addListener(behavior_manager);
	  error_log_manager->logProgress("Initialization successful.");
   }
   catch (GameException& ge)
   {
      error_log_manager->logException(ge);
      if (ge.getErrorNumber() == 1)
      {
         exit(1);
      } 
   }
}

size_t GameManager::getWindowHandle()
{
   return render_manager->getWindowHandle();
}

int GameManager::getWindowWidth()
{
   return render_manager->getWindowWidth();
}

int GameManager::getWindowHeight()
{
   return render_manager->getWindowHeight();
}

void GameManager::stopRendering()
{
	render_manager->stopRendering();
}

void GameManager::toggleLightSource(std::string light_name)
{
	render_manager->toggleLightSource(light_name);
}

void GameManager::resetTransformNode(std::string node_name)
{
	render_manager->resetTransformNode(node_name);
}

void GameManager::updateCameraRotation(float yaw, float pitch)
{
	render_manager->updateCameraRotation(yaw, pitch);
}

void GameManager::updateTransformNode(std::string transform_node_name, TransformType transform, double xVal, double yVal, double zVal, double qVal)
{
	render_manager->updateTransformNode(transform_node_name, transform, xVal, yVal, zVal, qVal);
}

void GameManager::updateCameraPosition(float x, float y, float z)
{
	render_manager->updateCameraPosition(x,y,z);
}

void GameManager::turnLightSourceOn(std::string light_name)
{
	render_manager->turnLightSourceOn( light_name);
}

void GameManager::turnLightSourceOff(std::string light_name)
{
	render_manager->turnLightSourceOff(light_name);
}

double* GameManager::parseDoubles(std::string& str)
{
   CSC2110::String* to_parse = CSC2110::String::convertToString(&str);
   ListArrayIterator<CSC2110::String>* tokens = to_parse->getTokens(',');

   int num_tokens = to_parse->numTokens(',');
   double* values = new double[num_tokens];

   int count = 0;
   while(tokens->hasNext())
   {
      CSC2110::String* temp = tokens->next();

      double val = temp->parseFloat();

      values[count] = val;
      count++;
      delete temp;
   }

   delete tokens;
   delete to_parse;

   return values;
}

double GameManager::parseDouble(std::string& str)
{
   return atof(str.c_str());
}

std::string GameManager::textFromChildNode(TiXmlNode* parent_node, const char* child_element_name)
{
   TiXmlNode* child_node = parent_node->FirstChild(child_element_name);
   if(child_node)
   {
   TiXmlElement* child_node_element = (TiXmlElement*) child_node->ToElement();
   std::string child_node_text = child_node_element->GetText();
   return child_node_text;
   }
   else
   {
   return "";
   }
}
