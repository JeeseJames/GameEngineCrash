#include "GameManager.h"
#include "MousePressBehavior.h"


void MousePressBehavior::executeAction(int x, int y)
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
		
   }
}