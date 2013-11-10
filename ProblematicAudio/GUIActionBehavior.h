#if !defined (GUI_ACTION_BEHAVIOR)
#define GUI_ACTION_BEHAVIOR

#include "GameBehavior.h"
#include <iostream>

class GUIActionBehavior : public GameBehavior
{

   private:


   public:
	  GUIActionBehavior(std::string k, std::string o, std::string a, std::string n, double mag, GameManager* gm) : GameBehavior(k,o,a,n,mag,gm){};
      virtual ~GUIActionBehavior(){};

      virtual void executeAction();
	  virtual void executeAction(int x, int y, float x_rel, float y_rel){}; //used in mouse move
	  virtual void executeAction(int x, int y){};//Mouse press and release use this
};

#endif
