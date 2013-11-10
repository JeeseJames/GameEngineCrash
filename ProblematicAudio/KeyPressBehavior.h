#if !defined (KEY_PRESS_BEHAVIOR)
#define KEY_PRESS_BEHAVIOR


#include <iostream>

class KeyPressBehavior
{

   private:
      std::string key;
      std::string object;
      std::string action;

      double magnitude;
      GameManager* game_manager;

   public:
      KeyPressBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm);
      virtual ~KeyPressBehavior();

      virtual std::string getKey();
      virtual void executeAction();

      static int compare_items(KeyPressBehavior* kpb1, KeyPressBehavior* kpb2);
      static int compare_keys(std::string* gk, KeyPressBehavior* kpb);

};

#endif
