#if !defined (BEHAVIOR_MANAGER)
#define BEHAVIOR_MANAGER

#include "TinyXML.h"
#include "CSC2110/TableAVL.h"
#include "KeyPressBehavior.h"
#include "KeyReleaseBehavior.h"
#include "KeyHeldBehavior.h"
#include "KeyState.h"
#include "MouseMoveBehavior.h"
#include "MousePressBehavior.h"
#include "MouseReleaseBehavior.h"
#include "MouseHeldBehavior.h"


class BehaviorManager : public InputListener
{
   private:
		GameManager* game_manager;
		void init();
		
		
		TableAVL<KeyPressBehavior, std::string>* key_press_behaviors;
		TableAVL<KeyReleaseBehavior, std::string>* key_release_behaviors;
		TableAVL<KeyHeldBehavior,std::string>* key_held_behaviors;
		TableAVL<MousePressBehavior,std::string>* mouse_press_behaviors;
		TableAVL<MouseReleaseBehavior,std::string>* mouse_release_behaviors;
		TableAVL<MouseMoveBehavior,std::string>* mouse_move_behaviors;
		TableAVL<MouseHeldBehavior,std::string>* mouse_held_behaviors;
		TableAVL<KeyState,std::string>* key_states;
		TableAVL<KeyState,std::string>* mouse_states;
		void loadBehaviorsFromXML(std::string file_name);
		
	public:
		BehaviorManager(GameManager* gm);
		virtual ~BehaviorManager();
		
		void keyPressed(std::string game_key);
		void keyReleased(std::string game_key);
		void mouseMoved(int mouse_x, int mouse_y, float mouse_x_rel, float mouse_y_rel);
		void mousePressed(int mouse_x, int mouse_y, std::string game_mouse);
		void mouseReleased(int mouse_x, int mouse_y, std::string game_mouse);
		  
		void checkInput();
		
};

#endif