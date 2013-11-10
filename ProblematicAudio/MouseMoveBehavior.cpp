#include "GameManager.h"
#include "MouseMoveBehavior.h"

MouseMoveBehavior::MouseMoveBehavior(std::string k, std::string o, std::string a, double mag, GameManager* gm)
{
   game_manager = gm;
   key = k;
   object = o;
   action = a;
   magnitude = mag;
}

MouseMoveBehavior::~MouseMoveBehavior()
{
   game_manager = NULL;
}

std::string MouseMoveBehavior::getKey()
{
   return key;
}

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

int MouseMoveBehavior::compare_items(MouseMoveBehavior* mmb1, MouseMoveBehavior* mmb2)
{
   std::string key_1 = mmb1->getKey();
   std::string key_2 = mmb2->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}

int MouseMoveBehavior::compare_keys(std::string* mm, MouseMoveBehavior* mmb)
{
   std::string key_1 = *mm;
   std::string key_2 = mmb->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}
