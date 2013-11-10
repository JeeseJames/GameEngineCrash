#include "GameManager.h"
#include "KeyHeldBehavior.h"


void KeyHeldBehavior::executeAction()
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
		if(action == "Jump")
		{
			game_manager->updateTransformNode(name,TRANSLATE,0,1*magnitude,0);
		}
		
		if(action =="Strafe Left")
		{
			game_manager->updateTransformNode(name,TRANSLATE,-1*magnitude, 0, 0);
		}
		if(action == "Strafe Right")
		{
			game_manager->updateTransformNode(name,TRANSLATE,1*magnitude, 0, 0);
		}
		if(action == "Forward")
		{
			game_manager->updateTransformNode(name,TRANSLATE,0,0,1*magnitude);
		}
		if(action == "Backward")
		{
			game_manager->updateTransformNode(name,TRANSLATE,0,0,-1*magnitude);
		}
		if(action == "Yaw")
		{
			game_manager->updateTransformNode(name,ROTATE,0,1,0,magnitude);
		}
		if(action == "Roll")
		{
			game_manager->updateTransformNode(name,ROTATE,0,0,1,magnitude);
		}
		if(action == "Pitch")
		{
			game_manager->updateTransformNode(name,ROTATE,1,0,0,1*magnitude);
		}
   }
   
}