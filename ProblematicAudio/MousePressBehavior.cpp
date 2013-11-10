#include "GameManager.h"
#include "MousePressBehavior.h"

MousePressBehavior::MousePressBehavior(std::string k, std::string o, std::string a, double mag, GameManager* gm)
{
   game_manager = gm;
   key = k;
   object = o;
   action = a;
   magnitude = mag;
   
   x_min = 0;
   x_max = 0;
   y_min = 0;
   y_max = 0;
}

MousePressBehavior::MousePressBehavior(std::string k, std::string o, std::string a, double mag, GameManager* gm, int _x_min, int _x_max, int _y_min, int _y_max)
{
   game_manager = gm;
   key = k;
   object = o;
   action = a;
   magnitude = mag;
   
   x_min = _x_min;
   x_max = _x_max;
   y_min = _y_min;
   y_max = _y_max;
}

MousePressBehavior::~MousePressBehavior()
{
   game_manager = NULL;
}

std::string MousePressBehavior::getKey()
{
   return key;
}

void MousePressBehavior::executeAction(int x, int y)
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
   else if (object == "ALL_LIGHTS")  //Really Dirty, How do we know Light1 and Light2 exist? we don't
   {
	if(action == "Toggle")
		{
		std::string light1 = "Light1";
		std::string light2 = "Light2";
		game_manager->toggleLightSource(light1);
		game_manager->toggleLightSource(light2);
		}
		if(action == "On")
		{
		std::string light1 = "Light1";
		std::string light2 = "Light2";
		game_manager->turnLightSourceOn(light1);
		game_manager->turnLightSourceOn(light2);
		}
		if(action == "Off")
		{
		std::string light1 = "Light1";
		std::string light2 = "Light2";
		game_manager->turnLightSourceOff(light1);
		game_manager->turnLightSourceOff(light2);
		}
   }
   else if(object == "Robbit Transform Node")
   {
		
   }
}

int MousePressBehavior::compare_items(MousePressBehavior* mpb1, MousePressBehavior* mpb2)
{
   std::string key_1 = mpb1->getKey();
   std::string key_2 = mpb2->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}

int MousePressBehavior::compare_keys(std::string* mk, MousePressBehavior* mpb)
{
   std::string key_1 = *mk;
   std::string key_2 = mpb->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}
