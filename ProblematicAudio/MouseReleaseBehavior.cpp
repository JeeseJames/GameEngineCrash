#include "GameManager.h"
#include "MouseReleaseBehavior.h"

MouseReleaseBehavior::MouseReleaseBehavior(std::string k, std::string o, std::string a, double mag, GameManager* gm)
{
   game_manager = gm;
   key = k;
   object = o;
   action = a;
   magnitude = mag;
   
}

MouseReleaseBehavior::~MouseReleaseBehavior()
{
   game_manager = NULL;
}

std::string MouseReleaseBehavior::getKey()
{
   return key;
}

bool MousePressBehavior::isClicked(int mouse_x_abs, int mouse_y_abs)
{
   bool test = (mouse_x_abs > x_min && mouse_x_abs < x_max && mouse_y_abs > y_min && mouse_y_abs < y_max);
   return test;
}


void MouseReleaseBehavior::executeAction(int x, int y)
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
   else if(object == "Robbit Transform Node")
   {
		
   }
}

int MouseReleaseBehavior::compare_items(MouseReleaseBehavior* mrb1, MouseReleaseBehavior* mrb2)
{
   std::string key_1 = mrb1->getKey();
   std::string key_2 = mrb2->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}

int MouseReleaseBehavior::compare_keys(std::string* mk, MouseReleaseBehavior* mrb)
{
   std::string key_1 = *mk;
   std::string key_2 = mrb->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}
