#if !defined (GAME_CONSTANTS)
#define GAME_CONSTANTS

#include <iostream>

   enum GameKey{W, A, S, D, X, ESCAPE, RIGHT_ARROW, LEFT_ARROW, UP_ARROW, DOWN_ARROW, INVALID_KEY};
   enum GameMouse{LEFT, RIGHT, INVALID_BUTTON};
   enum GameAction{FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT, ROTATE};
   enum GameObject{CAMERA};

static GameKey findKey(std::string key_str);
static GameObject findObject(std::string object_str);
static GameAction findAction(std::string action_str);

#endif
