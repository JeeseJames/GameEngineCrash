/*
	ALL Mouse Move Behaviors must have an accompanied by an Mouse Held Behaviors of the same key
	
	Mouse moves differ on which button is being held, only buttons with held behaviors are checked for being held
	Use key NONE to have a mouse move behavior when No key is down
	The order held behaviors are listed in behavior.xml gives priority to mouse move behaviors
*/
#if !defined (Mouse_MOVE_BEHAVIOR)
#define Mouse_MOVE_BEHAVIOR


#include <iostream>

class MouseMoveBehavior
{

   private:
      std::string key;
      std::string object;
      std::string action;

      double magnitude;
      GameManager* game_manager;

   public:
      MouseMoveBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm);
      virtual ~MouseMoveBehavior();

      virtual std::string getKey();
      virtual void executeAction(int x, int y, float x_rel, float y_rel);

      static int compare_items(MouseMoveBehavior* mmb1, MouseMoveBehavior* mmb2);
      static int compare_keys(std::string* mm, MouseMoveBehavior* mmb);

};

#endif
