#include "GameManager.h"
#include "KeyPressBehavior.h"




void KeyPressBehavior::executeAction()
{
	if (object == "Light")
   {
		if(action == "Toggle")
		{
		game_manager->toggleLightSource(name);
		}
		if(action == "On")
		{
		game_manager->turnLightSourceOn(name);
		}
		if(action == "Off")
		{
		game_manager->turnLightSourceOff(name);
		}
   }
   else if (object == "Camera")
   {
      if (action == "Forward")
      {
         game_manager->updateCameraPosition(0,0,-1*magnitude);
      }

      else if (action == "Backward")
      {
         game_manager->updateCameraPosition(0,0,1*magnitude);
      }

      else if (action == "Strafe Left")
      {
         game_manager->updateCameraPosition(-1*magnitude,0,0);
      }

      else if (action == "Strafe Right")
      {
         game_manager->updateCameraPosition(1*magnitude,0,0);
      }
   }
   else if(object == "Player")
   {
		if(action == "Reset")
		{
			game_manager->resetTransformNode(name);
		}
		if(action == "Jump")
		{
			std::string transform_node = name.substr(0,name.find(','));
			std::string sound_id = name.substr(name.find(',')+1, string::npos);
			game_manager->updateTransformNode(transform_node,INSTANT_TRANSLATE,0,1*magnitude,0);
			game_manager->playAudio(game_manager->parseDouble(sound_id), 0); 
		}
		
		if(action =="Strafe Left")
		{
			game_manager->updateTransformNode(name,INSTANT_TRANSLATE,-1*magnitude, 0, 0);
		}
		if(action == "Strafe Right")
		{
			game_manager->updateTransformNode(name,INSTANT_TRANSLATE,1*magnitude, 0, 0);
		}
		if(action == "Forward")
		{
			game_manager->updateTransformNode(name,INSTANT_TRANSLATE,0,0,1*magnitude);
		}
		if(action == "Backward")
		{
			game_manager->updateTransformNode(name,INSTANT_TRANSLATE,0,0,-1*magnitude);
		}
		if(action == "Yaw")
		{
			game_manager->updateTransformNode(name,INSTANT_ROTATE,0,1,0,magnitude);
		}
		if(action == "Roll")
		{
			game_manager->updateTransformNode(name,INSTANT_ROTATE,0,0,1,magnitude);
		}
		if(action == "Pitch")
		{
			game_manager->updateTransformNode(name,INSTANT_ROTATE,1,0,0,1*magnitude);
		}
   }
   else if(object == "GUI")
   {
		if(action == "Enable")
		{
		game_manager->enableRocket();	
		}
   }
   else if(object == "Audio")
   {
		if(action == "Play")
		{
			game_manager->playAudio(game_manager->parseDouble(name), magnitude); 
		}
		else if(action == "Pause BGM")
		{
			//game_manager->pauseBGM();
		}
		else if(action == "Pause")
		{
			//game_manager->pauseAudio(game_manager->parseDouble(name));
		}
		else if(action == "Volume Up")
		{
		//	game_manager->volumeUp(magnitude);
		}
		else if(action == "Volume Down")
		{
		//	game_manager->volumeDown(magnitude);
		}
   }
   else if(object == "Screen")
   {
		if(action == "Exit")
		{
			game_manager->stopRendering();
		}
		else if(action == "Full screen")
		{
			//game_manager->setFullScreen(name);
		}
   }
   else if(object == "Group")
   {
		if(action == "Load")
		{
	//	game_manager->loadGroup(name);	
		}
   }
}

