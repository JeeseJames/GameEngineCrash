#if !defined (Mouse_RELEASE_BEHAVIOR)
#define Mouse_RELEASE_BEHAVIOR


#include "GameBehavior.h"
#include <iostream>

class MouseReleaseBehavior : public GameBehavior
{


   public:
      MouseReleaseBehavior(std::string k, std::string o, std::string a, std::string n, double mag, GameManager* gm): GameBehavior(k,o,a,n,mag,gm){};
      virtual ~MouseReleaseBehavior(){};

      virtual void executeAction(int x, int y);
	  virtual void executeAction(){};
	  virtual void executeAction(int x, int y, float x_rel, float y_rel){}; //used in mouse move
};

#endif
