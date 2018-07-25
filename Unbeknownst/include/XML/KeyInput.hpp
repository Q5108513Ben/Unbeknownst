#pragma once

#include "SFML\Graphics.hpp"

// This is the KeyData struct, this contains all the necessary data to compare our own KeyData with
// SFML's sf::Event type. Our KeyData is found within the KeyBinding XML files, this is used to create
// our instances of KeyData to later be compared with SFML's sf::Event's during HandleEvent() calls
// found in the main game loop.

// We have Keyboard::Key or Mouse::Button depending on if our key input is from the keyboard
// or the mouse, pretty self explanatory. Obviously if our KeyData is a Keyboard input then the 
// sf::Mouse::Button will never be assigned anything and vice versa. This shouldn't be too much of 
// a problem since we will never require the sf::Mouse::Button if the KeyData is a Keyboard input.

// KeyData's are identified based on their action name, this is also found in the XML files however they
// are not directly stored with in the KeyData struct instead they are used as the 'Key' value of the 
// std::unordered_map used to store our KeyData.

struct KeyData {
	sf::Keyboard::Key keyCode;
	sf::Mouse::Button mouseButton;
};

static bool CompareKey(KeyData k, sf::Keyboard::Key e) {

	// CompareKey() is where we compare our own KeyData with the sf::Event SFML has given us.

	// It is worth noting that if the comparison returns true then that means that our KeyData matches the 
	// sf::Event and whatever code is written within the if statement that called this function will run. 
	// If the comparison fails then we just move onto the next comparison in the HandleEvent() function.

	if (k.keyCode == e) {

		return true;

	} 
	else {

		return false;

	}
}

static bool CompareButton(KeyData k, sf::Mouse::Button e) {

	// CompareButton() functions in the same way as CompareKey() except here we are looking at
	// mouse buttons rather than keyboard keys.

	if (k.mouseButton == e) {

		return true;

	}
	else {

		return false;

	}
}