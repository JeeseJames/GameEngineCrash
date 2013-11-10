/*
	
*/
#if !defined (Mouse_MOVE_BEHAVIOR)
#define Mouse_MOVE_BEHAVIOR


#include "GameBehavior.h"
#include <iostream>

class MouseMoveBehavior : public GameBehavior
{


   public:
      MouseMoveBehavior(std::string k, std::string o, std::string a, std::string n, double mag, GameManager* gm): GameBehavior(k,o,a,n,mag,gm){};
      virtual ~MouseMoveBehavior(){};

      virtual void executeAction(int x, int y, float x_rel, float y_rel);
	  virtual void executeAction(){};
	  virtual void executeAction(int x, int y){};//Mouse press and release use this

};

#endif
