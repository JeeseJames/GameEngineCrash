#include "GameManager.h"
#include "KeyReleaseBehavior.h"


void KeyReleaseBehavior::executeAction()
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
   else if(object == "Player")
   {
		if(action == "Jump")
		{
			game_manager->updateTransformNode(name,INSTANT_TRANSLATE,0,-1*magnitude,0);
		}
		
   }
}
