#include "Keyboard.h"

//--------------------------------------------------------------------------------------------------

bool Keyboard::KeyDown(Key key)
{
	static std::unordered_map<Key, bool> wasPressed;

	if (KeyPressed(key)) {
		if (!wasPressed[key])			
			return wasPressed[key] = true;
	}
	else
		wasPressed[key] = false;

	return false;
}

//--------------------------------------------------------------------------------------------------
