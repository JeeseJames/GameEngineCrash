#include "KeyState.h"

KeyState::KeyState(std::string k)
{
	is_down = false;
	key = k;
}

KeyState::~KeyState(){}

bool KeyState::isUp()
{
	return !is_down;
}

bool KeyState::isDown()
{
	return is_down;
}

void KeyState::setDown()
{
	is_down=true;
}

void KeyState::setUp()
{
	is_down=false;
}

void KeyState::toggle()
{
	if(is_down)
	{
		is_down=false;
	}
	else
	{
		is_down=true;
	}

}

std::string KeyState::getKey()
{
return key;
}

int KeyState::compare_items(KeyState* ks1, KeyState* ks2)
{
	std::string key_1 = ks1->getKey();
	std::string key_2 = ks2->getKey();
	int key_compare = key_1.compare(key_2);
	return key_compare;
}

int KeyState::compare_keys(std::string* sk, KeyState* ks)
{
	std::string key_1 = *sk;
	std::string key_2 = ks->getKey();
	int key_compare = key_1.compare(key_2);
	return key_compare;
}