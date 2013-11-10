#include "GameManager.h"
#include "MouseHeldBehavior.h"

MouseHeldBehavior::MouseHeldBehavior(std::string k, std::string o, std::string a, double mag, GameManager* gm)
{
   game_manager = gm;
   key = k;
   object = o;
   action = a;
   magnitude = mag;
}

MouseHeldBehavior::~MouseHeldBehavior()
{
   game_manager = NULL;
}

std::string MouseHeldBehavior::getKey()
{
   return key;
}

void MouseHeldBehavior::executeAction()
{
	  if (object == "Light1")
   {
		if(action == "Toggle")
		{
		game_manager->toggleLightSource(object);
		}
		if(action == "On")
		{
		game_manager->turnLightSourceOn(object);
		}
		if(action == "Off")
		{
		game_manager->turnLightSourceOff(object);
		}
   }
   else if (object == "Light2")
   {
		if(action == "Toggle")
		{
		game_manager->toggleLightSource(object);
		}
		if(action == "On")
		{
		game_manager->turnLightSourceOn(object);
		}
		if(action == "Off")
		{
		game_manager->turnLightSourceOff(object);
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
   else if(object == "Robbit Transform Node")
   {
		if(action == "Jump")
		{
			game_manager->updateTransformNode(object,INSTANT_TRANSLATE,0,1*magnitude,0);
		}
		
		if(action =="Strafe Left")
		{
			game_manager->updateTransformNode(object,TRANSLATE,-1*magnitude, 0, 0);
		}
		if(action == "Strafe Right")
		{
			game_manager->updateTransformNode(object,TRANSLATE,1*magnitude, 0, 0);
		}
		if(action == "Forward")
		{
			game_manager->updateTransformNode(object,TRANSLATE,0,0,1*magnitude);
		}
		if(action == "Backward")
		{
			game_manager->updateTransformNode(object,TRANSLATE,0,0,-1*magnitude);
		}
		if(action == "Yaw")
		{
			game_manager->updateTransformNode(object,ROTATE,0,1,0,magnitude);
		}
		if(action == "Roll")
		{
			game_manager->updateTransformNode(object,ROTATE,0,0,1,magnitude);
		}
		if(action == "Pitch")
		{
			game_manager->updateTransformNode(object,ROTATE,1,0,0,1*magnitude);
		}
   }
}

int MouseHeldBehavior::compare_items(MouseHeldBehavior* mhb1, MouseHeldBehavior* mhb2)
{
   std::string key_1 = mhb1->getKey();
   std::string key_2 = mhb2->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}

int MouseHeldBehavior::compare_keys(std::string* mk, MouseHeldBehavior* mhb)
{
   std::string key_1 = *mk;
   std::string key_2 = mhb->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}
