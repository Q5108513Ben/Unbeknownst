#pragma once

#include "SFML\Graphics.hpp"

// In SFML it seems keyboard events are treated differently to mouse events.

// Keyboard events store the key code in key.code
// Mouse events store the key code in mouseButton.button

// Because of this I have created an enum to differentiate between Keyboard Inputs and Mouse Inputs to 
// better align with SFML when comparing an sf::Event with my KeyData struct.

enum InputType {
	KeyboardInput,
	MouseInput
};

// This is the KeyData struct, this contains all the necessary data to compare our own KeyData with
// SFML's sf::Event type. Our KeyData is found within the KeyBinding XML files, this is used to create
// our instances of KeyData to be later compared with SFML's sf::Event's during HandleEvent() calls
// found in the main game loop.

// InputType seperates Keyboard and Mouse inputs as they both require different checks when comparing
// with the sf::Event's key code. This is seen in the function below.

// Lastly we have the Keyboard::Key or Mouse::Button depending on if our key input is from the keyboard
// or the mouse, pretty self explanatory.

struct KeyData {
	InputType inputType;
	sf::Keyboard::Key keyCode;
	sf::Mouse::Button mouseButton;
};

static bool CompareKey(KeyData k, sf::Keyboard::Key e) {

	// CompareKey() is where we compare our own KeyData with the sf::Event SFML has given us.

	// The reason we do each of these checks is already explained above, however it is worth noting that
	// if the comparison returns true then that means that our KeyData matches the sf::Event and whatever
	// code is written within the if statement that called this function will run. If the comparison 
	// fails then we just move onto the next comparison in the HandleEvent() function.

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