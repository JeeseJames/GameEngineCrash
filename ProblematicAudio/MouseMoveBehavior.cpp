#include "GameManager.h"
#include "MouseMoveBehavior.h"

void MouseMoveBehavior::executeAction(int x, int y, float x_rel, float y_rel)
{
   if (object == "Camera")
   {
		if(action == "Rotate")
		{
			game_manager->updateCameraRotation(x_rel*magnitude, y_rel*magnitude);
		}
		else if(action == "Reverse X Rotate")
		{
			game_manager->updateCameraRotation(-1*x_rel*magnitude, y_rel*magnitude);
		}
		else if(action == "Reverse Y Rotate")
		{
			game_manager->updateCameraRotation(1*x_rel*magnitude, -1*y_rel*magnitude);
		}
		else if(action == "Reverse Rotate")
		{
			game_manager->updateCameraRotation(-1*x_rel*magnitude, -1*y_rel*magnitude);
		}
   }
}
