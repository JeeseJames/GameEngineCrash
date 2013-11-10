#include "GameManager.h"
#include "GameBehavior.h"

GameBehavior::GameBehavior(std::string k, std::string o, std::string a, std::string n, double mag, GameManager* gm)//default value for n is "" (empty) via game manager getTextFromChild
{
   game_manager = gm;
   key = k;
   object = o;
   action = a;
   magnitude = mag;
   name = n;
}


GameBehavior::~GameBehavior()
{
   game_manager = NULL;
}

std::string GameBehavior::getKey()
{
   return key;
}

int GameBehavior::compare_items(GameBehavior* gb1, GameBehavior* gb2)
{
   std::string key_1 = gb1->getKey();
   std::string key_2 = gb2->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}

int GameBehavior::compare_keys(std::string* gk, GameBehavior* gb)
{
   std::string key_1 = *gk;
   std::string key_2 = gb->getKey();
   int key_compare = key_1.compare(key_2);
   return key_compare;
}
