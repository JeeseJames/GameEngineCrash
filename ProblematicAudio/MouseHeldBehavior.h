#if !defined (Mouse_HELD_BEHAVIOR)
#define Mouse_HELD_BEHAVIOR


#include <iostream>

class MouseHeldBehavior
{

   private:
      std::string key;
      std::string object;
      std::string action;

      double magnitude;
      GameManager* game_manager;

   public:
      MouseHeldBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm);
      virtual ~MouseHeldBehavior();

      virtual std::string getKey();
      virtual void executeAction();

      static int compare_items(MouseHeldBehavior* mhb1, MouseHeldBehavior* mhb2);
      static int compare_keys(std::string* mk, MouseHeldBehavior* mhb);

};

#endif
