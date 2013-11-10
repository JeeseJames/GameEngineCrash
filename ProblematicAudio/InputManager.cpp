#include "InputManager.h"
#include "GameManager.h"
#include "ErrorLogManager.h"

#include <sstream>
#include <iostream>
using namespace std;

//called on each and every frame!
void InputManager::checkInput()
{
   if (mouse_ois) mouse_ois->capture();
   if (keyboard_ois) keyboard_ois->capture();
   if (joystick_ois) joystick_ois->capture();
   
   //Check if key is down each and every frame
   
}

std::string InputManager::keyMap(const OIS::KeyEvent& e)
{
   std::string game_key = "INVALID_KEY";
   OIS::KeyCode key_code = e.key;

   if (key_code == OIS::KC_ESCAPE)
   {
      game_key = "ESCAPE";
   }
   else if (key_code == OIS::KC_SPACE) 
   {
      game_key = "SPACE";
   }
   else if (key_code == OIS::KC_RIGHT)
   {
      game_key = "RIGHT_ARROW";
   }
   else if (key_code == OIS::KC_LEFT)
   {
      game_key = "LEFT_ARROW";
   }
   else if (key_code == OIS::KC_UP)
   {
      game_key = "UP_ARROW";
   }
   else if (key_code == OIS::KC_DOWN)
   {
      game_key = "DOWN_ARROW";
   }
   else if (key_code == OIS::KC_A)
   {
      game_key = "A";
   }
    else if (key_code == OIS::KC_B)
   {
      game_key = "B";
   }
   else if (key_code == OIS::KC_C)
   {
      game_key = "C";
   }
   else if (key_code == OIS::KC_D)
   {
      game_key = "D";
   }
   else if (key_code == OIS::KC_E)
   {
      game_key = "E";
   }
   else if (key_code == OIS::KC_F)
   {
      game_key = "F";
   }
   else if (key_code == OIS::KC_G)
   {
      game_key = "H";
   }
   else if (key_code == OIS::KC_I)
   {
      game_key = "I";
   }
   else if (key_code == OIS::KC_J)
   {
      game_key = "J";
   }
   else if (key_code == OIS::KC_K)
   {
      game_key = "K";
   }
   else if (key_code == OIS::KC_L)
   {
      game_key = "L";
   }
   else if (key_code == OIS::KC_M)
   {
      game_key = "M";
   }
   else if (key_code == OIS::KC_N)
   {
      game_key = "N";
   }
   else if (key_code == OIS::KC_O)
   {
      game_key = "O";
   }
   else if (key_code == OIS::KC_P)
   {
      game_key = "P";
   }
   else if (key_code == OIS::KC_Q)
   {
      game_key = "Q";
   }
   else if (key_code == OIS::KC_R)
   {
      game_key = "R";
   }
   else if (key_code == OIS::KC_S)
   {
      game_key = "S";
   }
   else if (key_code == OIS::KC_T)
   {
      game_key = "T";
   }
   else if (key_code == OIS::KC_U)
   {
      game_key = "U";
   }
   else if (key_code == OIS::KC_V)
   {
      game_key = "V";
   }
   else if (key_code == OIS::KC_W)
   {
      game_key = "W";
   }
   else if (key_code == OIS::KC_X)
   {
      game_key = "X";
   }
   else if (key_code == OIS::KC_Y)
   {
      game_key = "Y";
   }
   else if (key_code == OIS::KC_Z)
   {
      game_key = "Z";
   }
   else if (key_code == OIS::KC_1)
   {
      game_key = "1";
   }
   else if (key_code == OIS::KC_2)
   {
      game_key = "2";
   }
   else if (key_code == OIS::KC_3)
   {
      game_key = "3";
   }
   else if (key_code == OIS::KC_4)
   {
      game_key = "4";
   }
   else if (key_code == OIS::KC_5)
   {
      game_key = "5";
   }
   else if (key_code == OIS::KC_6)
   {
      game_key = "6";
   }
   else if (key_code == OIS::KC_7)
   {
      game_key = "7";
   }
   else if (key_code == OIS::KC_8)
   {
      game_key = "8";
   }
   else if (key_code == OIS::KC_9)
   {
      game_key = "9";
   }
   else if (key_code == OIS::KC_0)
   {
      game_key = "0";
   }
   else if (key_code == OIS::KC_CAPITAL) //CAPS LOCK I assume? 
   {
      game_key = "CAPITAL";
   }
   else if (key_code == OIS::KC_NUMPAD1)
   {
      game_key = "NUMPAD1";
   }
   else if (key_code == OIS::KC_NUMPAD2)
   {
      game_key = "NUMPAD2";
   }
   else if (key_code == OIS::KC_NUMPAD3)
   {
      game_key = "NUMPAD3";
   }
   else if (key_code == OIS::KC_NUMPAD4)
   {
      game_key = "NUMPAD4";
   }
   else if (key_code == OIS::KC_NUMPAD5)
   {
      game_key = "NUMPAD5";
   }
   else if (key_code == OIS::KC_NUMPAD6)
   {
      game_key = "NUMPAD6";
   }
   else if (key_code == OIS::KC_NUMPAD7)
   {
      game_key = "NUMPAD7";
   }
   else if (key_code == OIS::KC_NUMPAD8)
   {
      game_key = "NUMPAD8";
   }
   else if (key_code == OIS::KC_NUMPAD9)
   {
      game_key = "NUMPAD9";
   }
   else if (key_code == OIS::KC_NUMPAD0)
   {
      game_key = "NUMPAD0";
   }
   else if (key_code == OIS::KC_MULTIPLY) //* on numeric keypad
   {
      game_key = "MULTIPLY";
   }
   else if (key_code == OIS::KC_NUMLOCK) 
   {
      game_key = "NUMLOCK";
   }
   else if (key_code == OIS::KC_SUBTRACT) //- on numeric keypad
   {
      game_key = "SUBTRACT";
   }
   else if (key_code == OIS::KC_ADD) // + on numeric keypad
   {
      game_key = "ADD";
   }
   else if (key_code == OIS::KC_DECIMAL) //. on numeric keypad
   {
      game_key = "DECIMAL";
   }
   else if (key_code == OIS::KC_NUMPADENTER)  //enter on numeric keypad
   {
      game_key = "NUMPADENETER";
   }
   else if (key_code == OIS::KC_DIVIDE) // / on numeric keypad
   {
      game_key = "DIVIDE";
   }
   else if (key_code == OIS::KC_MINUS)
   {
      game_key = "MINUS";
   }
   else if (key_code == OIS::KC_EQUALS)
   {
      game_key = "EQUALS";
   }
   else if (key_code == OIS::KC_BACK) //backspace
   {
      game_key = "BACK"; 
   }
   else if (key_code == OIS::KC_TAB)
   {
      game_key = "TAB";
   }
   else if (key_code == OIS::KC_LBRACKET)
   {
      game_key = "LBRACKET";
   }
   else if (key_code == OIS::KC_RBRACKET)
   {
      game_key = "RBRACKET";
   }
   else if (key_code == OIS::KC_RETURN) //Enter on main keyboard
   {
      game_key = "RETURN";
   }
   else if (key_code == OIS::KC_LCONTROL)
   {
      game_key = "LCONTROL";
   }
   else if (key_code == OIS::KC_RCONTROL)
   {
      game_key = "RCONTROL";
   }
   else if (key_code == OIS::KC_SEMICOLON)
   {
      game_key = "SEMICOLON";
   }
   else if (key_code == OIS::KC_APOSTROPHE)
   {
      game_key = "APOSTROPHE";
   }
   else if (key_code == OIS::KC_GRAVE) //accent, NOTICE change from OIS to game_key
   {
      game_key = "ACCENT";
   }
   else if (key_code == OIS::KC_LSHIFT)
   {
      game_key = "LSHIFT";
   }
   else if (key_code == OIS::KC_RSHIFT)
   {
      game_key = "RSHIFT";
   }
   else if (key_code == OIS::KC_BACKSLASH)
   {
      game_key = "BACKSLASH";
   }
   else if (key_code == OIS::KC_COMMA)
   {
      game_key = "COMMA";
   }
   else if (key_code == OIS::KC_PERIOD)
   {
      game_key = "PERIOD";
   }
   else if (key_code == OIS::KC_SLASH)
   {
      game_key = "SLASH";
   }
   else if (key_code == OIS::KC_LMENU) //left Alt, NOTICE change from OIS to game_key
   {
      game_key = "LALT";
   }
   else if (key_code == OIS::KC_RMENU) //right Alt, NOTICE change from OIS to game_key
   {
      game_key = "RALT";
   }
    else if (key_code == OIS::KC_F1) 
   {
      game_key = "F1";
   }
   else if (key_code == OIS::KC_F2) 
   {
      game_key = "F2";
   }
   else if (key_code == OIS::KC_F3) 
   {
      game_key = "F3";
   }
   else if (key_code == OIS::KC_F4) 
   {
      game_key = "F4";
   }
   else if (key_code == OIS::KC_F5) 
   {
      game_key = "F5";
   }
   else if (key_code == OIS::KC_F6) 
   {
      game_key = "F6";
   }
   else if (key_code == OIS::KC_F7) 
   {
      game_key = "F7";
   }
   else if (key_code == OIS::KC_F8) 
   {
      game_key = "F8";
   }
   else if (key_code == OIS::KC_F9) 
   {
      game_key = "F9";
   }
   else if (key_code == OIS::KC_F10) 
   {
      game_key = "F10";
   }
   else if (key_code == OIS::KC_F11) 
   {
      game_key = "F11";
   }
   else if (key_code == OIS::KC_F12) 
   {
      game_key = "F12";
   }
   else if (key_code == OIS::KC_F13) 
   {
      game_key = "F13";
   }
   else if (key_code == OIS::KC_F14) 
   {
      game_key = "F14";
   }
   else if (key_code == OIS::KC_F15) 
   {
      game_key = "F15";
   }
   else if (key_code == OIS::KC_SCROLL)  //Scroll Lock
   {
      game_key = "SCROLL";
   }
   

   return game_key;
}

std::string InputManager::mouseMap(const OIS::MouseButtonID id)
{
   std::string game_mouse = "INVALID_BUTTON";
   int mouse_code = id;

   if (mouse_code == OIS::MB_Left)
   {
      game_mouse = "LEFT";
   }
   else if (mouse_code == OIS::MB_Right)
   {
      game_mouse = "RIGHT";
   }
   else if(mouse_code == OIS::MB_Middle)
   {
	  game_mouse = "MIDDLE";
   }
   else if(mouse_code == OIS::MB_Button3)
   {
	  game_mouse = "BUTTON3";
   }
   else if(mouse_code == OIS::MB_Button4)
   {
	  game_mouse = "BUTTON4";
   }
   else if(mouse_code == OIS::MB_Button5)
   {
	  game_mouse = "BUTTON5";
   }
   else if(mouse_code == OIS::MB_Button6)
   {
	  game_mouse = "BUTTON6";
   }
   else if(mouse_code == OIS::MB_Button7)
   {
	  game_mouse = "BUTTON7";
   }

   return game_mouse;
}

//callback
bool InputManager::mousePressed(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
//cout << "MP" << endl;
   //notify each of the listeners
   ListArrayIterator<InputListener>* iter = input_listeners->iterator();
   while(iter->hasNext())
   {
      InputListener* listener = iter->next();

      std::string game_mouse = mouseMap(id);
      int x_loc = (int) e.state.X.abs * (window_width / 50.0);
      int y_loc = (int) e.state.Y.abs * (window_height / 50.0);
      listener->mousePressed(x_loc, y_loc, game_mouse);  //absolute location of mouse when pressed and which button was pressed
   }
   delete iter;

   return true;
}

//callback
bool InputManager::mouseReleased(const OIS::MouseEvent& e, OIS::MouseButtonID id)
{
//cout << "MR" << endl;
   //notify each of the listeners
   ListArrayIterator<InputListener>* iter = input_listeners->iterator();
   while(iter->hasNext())
   {
      InputListener* listener = iter->next();

      std::string game_mouse = mouseMap(id);
      int x_loc = (int) e.state.X.abs * (window_width / 50.0);
      int y_loc = (int) e.state.Y.abs * (window_height / 50.0);
      listener->mouseReleased(x_loc, y_loc, game_mouse);  //absolute location of mouse when released and which button was released
   }
   delete iter;

   return true;
}

//callback
bool InputManager::mouseMoved(const OIS::MouseEvent& e)
{
//cout << "MM" << endl;
   //notify each of the listeners
   ListArrayIterator<InputListener>* iter = input_listeners->iterator();
   while(iter->hasNext())
   {
      InputListener* listener = iter->next();
      int x_loc = (int) e.state.X.abs * (window_width / 50.0);
      int y_loc = (int) e.state.Y.abs * (window_height / 50.0);
      float x_rel = e.state.X.rel;
      float y_rel = e.state.Y.rel;
      listener->mouseMoved(x_loc, y_loc, x_rel, y_rel);  //current location of the mouse (absolute coords and relative coords)
   }
   delete iter;

   return true;
}

//callback
bool InputManager::keyPressed(const OIS::KeyEvent& e)
{
//cout << "KP" << endl;
   //notify each of the listeners
   ListArrayIterator<InputListener>* iter = input_listeners->iterator();

   while(iter->hasNext())
   {
      InputListener* listener = iter->next();
      listener->keyPressed(keyMap(e));
   }
   delete iter;

   return true;
}

//callback
bool InputManager::keyReleased(const OIS::KeyEvent& e)
{
//cout << "KR" << endl;
   //notify each of the listeners
   ListArrayIterator<InputListener>* iter = input_listeners->iterator();
   while(iter->hasNext())
   {
      InputListener* listener = iter->next();
      listener->keyReleased(keyMap(e));
   }
   delete iter;

   return true;
}

InputManager::InputManager(GameManager* game_manager)
{
   input_manager_ois = NULL;
   keyboard_ois = NULL;
   mouse_ois = NULL;
   joystick_ois = NULL;

   input_listeners = new ListArray<InputListener>();

   init(game_manager);

   //addListener(game_manager);

   window_width = game_manager->getWindowWidth();
   window_height = game_manager->getWindowHeight();
}

InputManager::~InputManager()
{
   free();

   input_manager_ois = NULL;
   keyboard_ois = NULL;
   mouse_ois = NULL;
   joystick_ois = NULL;

   //delete each of the listeners
/*
   ListArrayIterator<InputListener>* iter = input_listeners->iterator();
   while(iter->hasNext())
   {
      InputListener* listener = iter->next();
   }
   delete iter;
*/
   delete input_listeners;
}

void InputManager::addListener(InputListener* listener)
{
   input_listeners->add(listener);
}

void InputManager::free()
{
   if (input_manager_ois)
   {
      input_manager_ois->destroyInputSystem(input_manager_ois);
   }
}

void InputManager::init(GameManager* game_manager)
{
   try
   {
      OIS::ParamList p1;
      std::ostringstream windowHndStr;
      size_t window_handle = game_manager->getWindowHandle();

      size_t handle = window_handle;
      windowHndStr << handle;
      p1.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

      input_manager_ois = OIS::InputManager::createInputSystem(p1);

      if (input_manager_ois->getNumberOfDevices(OIS::OISKeyboard) > 0)
      {
         keyboard_ois = static_cast<OIS::Keyboard*>(input_manager_ois->createInputObject(OIS::OISKeyboard, true));
         keyboard_ois->setEventCallback(this);  //forwards the information to all registered listeners
      }

      if (input_manager_ois->getNumberOfDevices(OIS::OISMouse) > 0)
      {
         mouse_ois = static_cast<OIS::Mouse*>(input_manager_ois->createInputObject(OIS::OISMouse, true));
         mouse_ois->setEventCallback(this);  //forwards the information to all registered listeners
      }

      if (input_manager_ois->getNumberOfDevices(OIS::OISJoyStick) > 0)
      {
         joystick_ois = static_cast<OIS::JoyStick*>(input_manager_ois->createInputObject(OIS::OISJoyStick, true));
         joystick_ois->setEventCallback(this);  //forwards the information to all registered listeners
      }
   }

   catch(std::exception& e)  //may be possible to get a good error message from ois this way
   {
      THROW_EXCEPTION(1, e.what());  //error number 1 refers to an error that is too serious to continue
   }

   catch(...)  //catch any other type of exception thrown by OIS, won't be able to access the actual error message
   {
      THROW_EXCEPTION(1, "Input Manager Initialization Error");  //error number 1 refers to an error that is too serious to continue
   }
   game_manager->logProgress("Input Manager Initialized");
}
