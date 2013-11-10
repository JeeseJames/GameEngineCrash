#if !defined (GAME_BEHAVIOR)
#define GAME_BEHAVIOR


#include <iostream>

class GameBehavior
{

   protected:
      std::string key;
      std::string object;
      std::string action;
	  std::string name;

      double magnitude;
      GameManager* game_manager;

   public:
	  GameBehavior(std::string k, std::string o, std::string a, std::string n, double mag, GameManager* gm);
      virtual ~GameBehavior();

      virtual std::string getKey();
      virtual void executeAction()=0; //Mouse will have to implement this empty
	  virtual void executeAction(int x, int y, float x_rel, float y_rel)=0; //used in mouse move
	  virtual void executeAction(int x, int y)=0;//Mouse press and release use this

      static int compare_items(GameBehavior* gb1, GameBehavior* gb2);
      static int compare_keys(std::string* gk, GameBehavior* gb);

};

#endif
