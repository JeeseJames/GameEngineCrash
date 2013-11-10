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
	//delete each KeyPressBehavior via iteration
   delete key_states;
   delete key_press_behaviors;
   delete key_release_behaviors;
   delete mouse_move_behaviors;
   delete mouse_press_behaviors;
   delete mouse_release_behaviors;
   delete mouse_held_behaviors;
}

void BehaviorManager::init()
{
	loadBehaviorsFromXML("behaviors.xml");
}

void BehaviorManager::loadBehaviorsFromXML(std::string file_name)
{
   key_press_behaviors = new TableAVL<KeyPressBehavior, std::string>(&KeyPressBehavior::compare_items, &KeyPressBehavior::compare_keys);
   key_release_behaviors = new TableAVL<KeyReleaseBehavior, std::string>(&KeyReleaseBehavior::compare_items, &KeyReleaseBehavior::compare_keys);
   key_held_behaviors = new TableAVL<KeyHeldBehavior, std::string>(&KeyHeldBehavior::compare_items, &KeyHeldBehavior::compare_keys);
   key_states = new TableAVL<KeyState,std::string>(&KeyState::compare_items, &KeyState::compare_keys);
   mouse_states = new TableAVL<KeyState,std::string>(&KeyState::compare_items, &KeyState::compare_keys);
   mouse_press_behaviors = new TableAVL<MousePressBehavior, std::string>(&MousePressBehavior::compare_items, &MousePressBehavior::compare_keys);
   mouse_release_behaviors = new TableAVL<MouseReleaseBehavior, std::string>(&MouseReleaseBehavior::compare_items, &MouseReleaseBehavior::compare_keys);
   mouse_move_behaviors = new TableAVL<MouseMoveBehavior, std::string>(&MouseMoveBehavior::compare_items, &MouseMoveBehavior::compare_keys);
   mouse_held_behaviors = new TableAVL<MouseHeldBehavior, std::string>(&MouseHeldBehavior::compare_items, &MouseHeldBehavior::compare_keys);
	  
 

   
   
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

            if (behavior_type_text == "key_press")
            {
               std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               KeyPressBehavior* kpb = new KeyPressBehavior(behavior_key_text, behavior_object_text, behavior_action_text, magnitude, game_manager);
               key_press_behaviors->tableInsert(kpb);
            }

            else if (behavior_type_text == "key_release")
            {
               std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               KeyReleaseBehavior* krb = new KeyReleaseBehavior(behavior_key_text, behavior_object_text, behavior_action_text, magnitude, game_manager);
               key_release_behaviors->tableInsert(krb);
            }

            else if(behavior_type_text == "key_held")
			{
			   std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               KeyHeldBehavior* khb = new KeyHeldBehavior(behavior_key_text, behavior_object_text, behavior_action_text, magnitude, game_manager);
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
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               MousePressBehavior* mpb = new MousePressBehavior(behavior_key_text, behavior_object_text, behavior_action_text, magnitude, game_manager);
               mouse_press_behaviors->tableInsert(mpb);
			}
			
			else if(behavior_type_text =="mouse_release")
			{
			   std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               MouseReleaseBehavior* mrb = new MouseReleaseBehavior(behavior_key_text, behavior_object_text, behavior_action_text, magnitude, game_manager);
               mouse_release_behaviors->tableInsert(mrb);
			}
			
			else if (behavior_type_text == "mouse_held")
            {
			   std::string behavior_key_text = GameManager::textFromChildNode(behavior_node, "key");
               std::string behavior_object_text = GameManager::textFromChildNode(behavior_node, "object");
               std::string behavior_action_text = GameManager::textFromChildNode(behavior_node, "action");
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               MouseHeldBehavior* mhb = new MouseHeldBehavior(behavior_key_text, behavior_object_text, behavior_action_text, magnitude, game_manager);
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
               std::string behavior_magnitude_text = GameManager::textFromChildNode(behavior_node, "magnitude");
               double magnitude = GameManager::parseDouble(behavior_magnitude_text);
                  
               MouseMoveBehavior* mmb = new MouseMoveBehavior(behavior_key_text, behavior_object_text, behavior_action_text, magnitude, game_manager);
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

void BehaviorManager::keyPressed(std::string game_key)
{

   if (game_key == "ESCAPE")
   {
      game_manager->stopRendering();
      return;
   }

   //store the KeyPressedBehaviors in a table with the GameKey as the search key
   KeyPressBehavior* kpb = key_press_behaviors->tableRetrieve(&game_key);

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
   KeyReleaseBehavior* krb = key_release_behaviors->tableRetrieve(&game_key);

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
	
	MouseMoveBehavior* mmb = mouse_move_behaviors->tableRetrieve(&name);
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
	MousePressBehavior* mpb = mouse_press_behaviors->tableRetrieve(&game_mouse);
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
	MouseReleaseBehavior* mrb = mouse_release_behaviors->tableRetrieve(&game_mouse);
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
			KeyHeldBehavior* khb = ( key_held_behaviors->tableRetrieve( &name ) );
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
			MouseHeldBehavior* mhb = ( mouse_held_behaviors->tableRetrieve( &name ) );
			mhb->executeAction();
		}
	}
}

