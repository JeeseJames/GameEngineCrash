#if !defined (Mouse_RELEASE_BEHAVIOR)
#define Mouse_RELEASE_BEHAVIOR


#include <iostream>

class MouseReleaseBehavior
{

   private:
      std::string key;
      std::string object;
      std::string action;

      double magnitude;
      GameManager* game_manager;

   public:
      MouseReleaseBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm);
      virtual ~MouseReleaseBehavior();

      virtual std::string getKey();
      virtual void executeAction(int x, int y);

      static int compare_items(MouseReleaseBehavior* mrb1, MouseReleaseBehavior* mrb2);
      static int compare_keys(std::string* mk, MouseReleaseBehavior* mrb);

};

#endif
