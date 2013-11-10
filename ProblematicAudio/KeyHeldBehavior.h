
#if !defined (KEY_HELD_BEHAVIOR)
#define KEY_HELD_BEHAVIOR


#include <iostream>

class KeyHeldBehavior : public GameBehavior
{


   public:
      KeyHeldBehavior(std::string k, std::string o, std::string a, std::string n, double mag, GameManager* gm): GameBehavior(k,o,a,n,mag,gm){};
      virtual ~KeyHeldBehavior(){};
      virtual void executeAction();
	  virtual void executeAction(int x, int y, float x_rel, float y_rel){}; //used in mouse move
	  virtual void executeAction(int x, int y){};//Mouse press and release use this
};

#endif
