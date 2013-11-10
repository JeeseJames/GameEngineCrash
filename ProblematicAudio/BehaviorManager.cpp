#include "GameManager.h"
#include "BehaviorManager.h"

using namespace std;

BehaviorManager::BehaviorManager(GameManager* gm)
{
	game_manager = gm;
	init();
}

BehaviorManager::~BehaviorManager()
{
cout<<"Destorying Behavior Manager"<<endl;
   AVLTreeIterator<GameBehavior>* iter = key_press_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }

   delete iter;
   delete key_press_behaviors;

   iter = key_release_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }
   
   delete iter;
   delete key_release_behaviors;
   
   iter = key_held_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }
   
   delete iter;
   delete key_held_behaviors;
   
   iter = mouse_move_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }
   
   delete iter;
   delete mouse_move_behaviors;
   
   iter = mouse_move_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }
   
   delete iter;
   delete mouse_press_behaviors;
   
   iter = mouse_move_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }
   
   delete iter;
   delete mouse_release_behaviors;
   iter = mouse_move_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }
   
   delete iter;
   delete mouse_held_behaviors;
   
   iter = gui_action_behaviors->tableIterator();
   while(iter->hasNext())
   {
      GameBehavior* gb = iter->next();
      delete gb;
   }
   
   delete iter;
   delete gui_action_behaviors;
   
   
   AVLTreeIterator<KeyState>* ksiter = key_states->tableIterator();
      while(ksiter->hasNext())
   {
      KeyState* ks = ksiter->next();
      delete ks;
   }
   delete ksiter;
   delete key_states;
   
   ksiter = mouse_states->tableIterator();
   
      while(ksiter->hasNext())
   {
      KeyState* ks = ksiter->next();
      delete ks;
   }
   delete ksiter;
   delete mouse_states;
}

void BehaviorManager::init()
{
	loadBehaviorsFromXML("behaviors.xml");
}

void BehaviorManager::loadBehaviorsFromXML(std::string file_name)
{
   gui_action_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
   key_press_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
   key_release_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
   key_held_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
   key_states = new TableAVL<KeyState,std::string>(&KeyState::compare_items, &KeyState::compare_keys);
   mouse_states = new TableAVL<KeyState,std::string>(&KeyState::compare_items, &KeyState::compare_keys);
   mouse_press_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
   mouse_release_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
   mouse_move_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
   mouse_held_behaviors = new TableAVL<GameBehavior, std::string>(&GameBehavior::compare_items, &GameBehavior::compare_keys);
	  
 

   
   
   TiXmlDocument doc(file_name.c_str());
   if (doc.LoadFile())
   {

      TiXmlNode* behaviors_tree = doc.FirstChild("behaviors");
      if (behaviors_tree)
      {
         //Enumerate behavior objects (eventually, child will be false and loop will terminate)
         for(TiXmlNode* behavior_node = behaviors_tree->FirstChild(); behavior_node; behavior_node = behavior_node->NextSibling())
         {
            std::string behavior_type_text = GameManager::textFromChildNode(behavior_node, "type");

            if(behavior_type_text == "gui_action")
			{
				std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               GUIActionBehavior* gab = new GUIActionBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               gui_action_behaviors->tableInsert(gab);
				
			}
			else if (behavior_type_text == "key_press")
            {
               std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               KeyPressBehavior* kpb = new KeyPressBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               key_press_behaviors->tableInsert(kpb);
            }

            else if (behavior_type_text == "key_release")
            {
               std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               KeyReleaseBehavior* krb = new KeyReleaseBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               key_release_behaviors->tableInsert(krb);
            }

            else if(behavior_type_text == "key_held")
			{
			   std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               KeyHeldBehavior* khb = new KeyHeldBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               key_held_behaviors->tableInsert(khb);
			   //make and add KeyState
			   KeyState* ks = new KeyState(behavior_key_text);
			   key_states->tableInsert(ks);
			   
			}
			else if(behavior_type_text =="mouse_press")
			{
			   std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               GameBehavior* mpb = new MousePressBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               mouse_press_behaviors->tableInsert(mpb);
			}
			
			else if(behavior_type_text =="mouse_release")
			{
			   std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               MouseReleaseBehavior* mrb = new MouseReleaseBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               mouse_release_behaviors->tableInsert(mrb);
			}
			
			else if (behavior_type_text == "mouse_held")
            {
			   std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               MouseHeldBehavior* mhb = new MouseHeldBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               mouse_held_behaviors->tableInsert(mhb);
			   
			   //make and add KeyState for the mousebutton
			   KeyState* ms = new KeyState(behavior_key_text);
			   mouse_states->tableInsert(ms);
            }
			
			else if (behavior_type_text == "mouse_move")
            {
               std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
			   std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
			   std::string behavior_name_text = GameManager::textFromChildNode(behavior_node, "name");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               MouseMoveBehavior* mmb = new MouseMoveBehavior(behavior_key_text, behavior_object_text, behavior_action_text, behavior_name_text, magnitude, game_manager);
               mouse_move_behaviors->tableInsert(mmb);
            }
         }
      }

   }
   else 
   {
      THROW_EXCEPTION(1, "Failed to find the behavior XML file.");
   }
}
void BehaviorManager::executeGUIAction(std::string gui_key)
{
	GameBehavior* gab = gui_action_behaviors->tableRetrieve(&gui_key);
	if(gab)
	{
		gab->executeAction();
	}
}
void BehaviorManager::keyPressed(std::string game_key)
{

   if (game_key == "ESCAPE")  //I have decided to leave this hard coded in, just in case an exit is not defined in behaviors.xml
   {
      game_manager->stopRendering();
      return;
   }

   //store the KeyPressedBehaviors in a table with the GameKey as the search key
   GameBehavior* kpb = key_press_behaviors->tableRetrieve(&game_key);

   KeyState* ks = key_states->tableRetrieve(&game_key);
	if(ks)
	{
		ks->setDown();
	}
   if (kpb)
   {
      kpb->executeAction();
   }
}
void BehaviorManager::keyReleased(std::string game_key)
{
	//store the KeyPressedBehaviors in a table with the GameKey as the search key
   GameBehavior* krb = key_release_behaviors->tableRetrieve(&game_key);

    KeyState* ks = key_states->tableRetrieve(&game_key);
	if(ks)
	{
		ks->setUp();
	}
   
   if (krb)
   {

      krb->executeAction();
   }
}

void BehaviorManager::mouseMoved(int mouse_x, int mouse_y, float mouse_x_rel, float mouse_y_rel)
{

	AVLTreeIterator<KeyState>* iter = mouse_states->tableIterator(); 
	KeyState* ms;
	std::string name = "NONE";
	
	game_manager->rocketMouseMoved(mouse_x, mouse_y);
	
	GameBehavior* mmb = mouse_move_behaviors->tableRetrieve(&name);
	if(mmb)
	{
		mmb->executeAction(mouse_x, mouse_y, mouse_x_rel, mouse_y_rel); 
		return;//gives TOP PRIORITY to mouse move behavior of no key held down
	}
	
	name = "LEFT";
	mmb = mouse_move_behaviors->tableRetrieve(&name);
	ms = mouse_states->tableRetrieve(&name);
	if(ms)
	{
		if(mmb)
		{
			if(ms->isDown())
			{
				mmb->executeAction(mouse_x, mouse_y, mouse_x_rel, mouse_y_rel); 
				return;//gives 2nd PRIORITY to mouse move behavior of LEFT key held down
			}
		}
	}
	name = "RIGHT";
	mmb = mouse_move_behaviors->tableRetrieve(&name);
	ms = mouse_states->tableRetrieve(&name);
	if(ms)
	{
		if(mmb)
		{
			if(ms->isDown())
			{
				mmb->executeAction(mouse_x, mouse_y, mouse_x_rel, mouse_y_rel); 
				return;//gives 3rd PRIORITY to mouse move behavior of RIGHT key held down
			}
		}
	}
	while(iter->hasNext())
	{
	ms=iter->next();
		if(ms->isDown())
		{
			std::string mouse_key = ms->getKey();
			mmb = mouse_move_behaviors->tableRetrieve(&mouse_key);
			if(mmb)
			{
				mmb->executeAction(mouse_x, mouse_y, mouse_x_rel, mouse_y_rel);
				return; //gives next highest Priority to Button 3
			}
		}
	}
}
void BehaviorManager::mousePressed(int mouse_x, int mouse_y, std::string game_mouse)
{
	KeyState* ms = mouse_states->tableRetrieve(&game_mouse);
	GameBehavior* mpb = mouse_press_behaviors->tableRetrieve(&game_mouse);
	game_manager->rocketMousePressed(mouse_x, mouse_y, game_manager->parseDouble(game_mouse));
	if(ms)
	{
		ms->setDown();
	}
	if(mpb)
	{
		mpb->executeAction(mouse_x, mouse_y);
	}
		
}
void BehaviorManager::mouseReleased(int mouse_x, int mouse_y, std::string game_mouse)
{
	KeyState* ms = mouse_states->tableRetrieve(&game_mouse);
	GameBehavior* mrb = mouse_release_behaviors->tableRetrieve(&game_mouse);
	game_manager->rocketMouseReleased(mouse_x,mouse_y,game_manager->parseDouble(game_mouse));
	if(ms)
	{
		ms->setUp();
	}
	if(mrb)
	{
		mrb->executeAction(mouse_x, mouse_y);
	}
}


void BehaviorManager::checkInput() //Called every frame, checks if a key is held since last frame
{
	AVLTreeIterator<KeyState>* iter = key_states->tableIterator(); 
	KeyState* ks;
	std::string name;
	while(iter->hasNext())
	{

		ks = iter->next();
		if(ks->isDown())
		{
			name = ks->getKey();
			GameBehavior* khb = ( key_held_behaviors->tableRetrieve( &name ) );
			khb->executeAction();
		}
	}
	
	iter = mouse_states->tableIterator();
	KeyState* ms;
	while(iter->hasNext())
	{

		ms = iter->next();
		if(ms->isDown())
		{
			name = ms->getKey();
			GameBehavior* mhb = ( mouse_held_behaviors->tableRetrieve( &name ) );
			mhb->executeAction();
		}
	}
}

