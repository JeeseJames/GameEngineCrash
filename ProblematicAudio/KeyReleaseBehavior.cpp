#include "GameManager.h"
#include "KeyReleaseBehavior.h"

KeyReleaseBehavior::KeyReleaseBehavior(std::string k, std::string o, std::string a, double mag, GameManager* gm)
{
   game_manager = gm;
   key = k;
   object = o;
   action = a;
   magnitude = mag;
}

KeyReleaseBehavior::~KeyReleaseBehavior()
{
   game_manager = NULL;
}

std::string KeyReleaseBehavior::getKey()
{
   return key;
}

void KeyReleaseBehavior::executeAction()
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
   else if(object == "Robbit Transform Node")
   {
		if(action == "Jump")
		{
			game_manager->updateTransformNode(object,INSTANT_TRANSLATE,0,-1*magnitude,0);
		}
		
   }
}

int KeyReleaseBehavior::compare_items(KeyReleaseBehavior* krb1, KeyReleaseBehavior* krb2)
{
   std::string key_1 = krb1->getKey();
   std::string key_2 = krb2->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}

int KeyReleaseBehavior::compare_keys(std::string* gk, KeyReleaseBehavior* krb)
{
   std::string key_1 = *gk;
   std::string key_2 = krb->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}
