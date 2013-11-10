#include "GameConstants.h"

//methods to convert from XML file text to game enums
static GameKey findKey(std::string key_str)
{
   if (key_str == "W") return W;
   else if (key_str == "A") return A;
   else if (key_str == "S") return S;
   else if (key_str == "D") return D;
   else if (key_str == "X") return X;
}

static GameObject findObject(std::string object_str)
{
   if (object_str == "camera") return CAMERA;
}

static GameAction findAction(std::string action_str)
{
   if (action_str == "forward") return FORWARD;
   else if (action_str == "backward") return BACKWARD;
   else if (action_str == "strafe_left") return STRAFE_LEFT;
   else if (action_str == "strafe_right") return STRAFE_RIGHT;
   else if (action_str == "rotate") return ROTATE;
}
