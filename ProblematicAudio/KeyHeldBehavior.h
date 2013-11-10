
#if !defined (KEY_HELD_BEHAVIOR)
#define KEY_HELD_BEHAVIOR


#include <iostream>

class KeyHeldBehavior
{

   private:
      std::string key;
      std::string object;
      std::string action;

      double magnitude;
      GameManager* game_manager;

   public:
      KeyHeldBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm);
      virtual ~KeyHeldBehavior();

      virtual std::string getKey();
      virtual void executeAction();

      static int compare_items(KeyHeldBehavior* khb1, KeyHeldBehavior* khb2);
      static int compare_keys(std::string* gk, KeyHeldBehavior* khb);

};

#endif
