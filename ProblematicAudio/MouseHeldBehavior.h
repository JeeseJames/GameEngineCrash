#if !defined (Mouse_HELD_BEHAVIOR)
#define Mouse_HELD_BEHAVIOR


#include "GameBehavior.h"
#include <iostream>

class MouseHeldBehavior : public GameBehavior
{


   public:
      MouseHeldBehavior(std::string k, std::string o, std::string a, std::string n, double mag, GameManager* gm): GameBehavior(k,o,a,n,mag,gm){};
      virtual ~MouseHeldBehavior(){};

      virtual void executeAction();
	  virtual void executeAction(int x, int y, float x_rel, float y_rel){}; //used in mouse move
	  virtual void executeAction(int x, int y){};//Mouse press and release use this

};

#endif
