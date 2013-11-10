#if !defined (Mouse_PRESS_BEHAVIOR)
#define Mouse_PRESS_BEHAVIOR


#include <iostream>

class MousePressBehavior
{

   private:
      std::string key;
      std::string object;
      std::string action;

      double magnitude;
      GameManager* game_manager;
	  
	  int x_min;
      int x_max;
      int y_min;
      int y_max;

   public:
      MousePressBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm, int _x_min, int _x_max, int _y_min, int _y_max);
      MousePressBehavior(std::string key, std::string object, std::string action, double magnitude, GameManager* gm);
     virtual ~MousePressBehavior();

      virtual std::string getKey();
      virtual void executeAction(int x, int y);
	  bool isClicked(int mouse_x, int mouse_y);

      static int compare_items(MousePressBehavior* mpb1, MousePressBehavior* mpb2);
      static int compare_keys(std::string* mk, MousePressBehavior* mpb);

};

#endif
