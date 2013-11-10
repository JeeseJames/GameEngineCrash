#if !defined (KEY_RELEASE_BEHAVIOR)
#define KEY_RELEASE_BEHAVIOR

#include <iostream>

class KeyReleaseBehavior
{

   private:
      std::string key;
      std::string object;
      std::string action;

      double magnitude;
      GameManager* game_manager;

   public:
      KeyReleaseBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm);
      virtual ~KeyReleaseBehavior();

      virtual std::string getKey();
      virtual void executeAction();

      static int compare_items(KeyReleaseBehavior* krb1, KeyReleaseBehavior* krb2);
      static int compare_keys(std::string* gk, KeyReleaseBehavior* krb);

};

#endif
