#if !defined (KEY_STATE)
#define KEY_STATE

#include <iostream>

class KeyState
{
	private: 
		bool is_down;
		std::string key;
		
	public:
		KeyState(std::string k);
		virtual ~KeyState();
		bool isUp();
		bool isDown();
		void setDown();
		void setUp();
		void toggle();
		virtual std::string getKey();

		static int compare_items(KeyState* ks1, KeyState* ks2);
		static int compare_keys(std::string* sk, KeyState* ks);
		
};
#endif