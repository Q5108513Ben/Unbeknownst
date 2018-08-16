#include "XML\KeyBindings.hpp"
#include "tinyxml2.h"
#include <iostream>

KeyBindings KeyBindings::keyBinds;

void KeyBindings::InitialiseKeyBinds() {

	// This initial block of code is to retrieve a pointer to the first block of 'Key' data in
	// the KeyBindings.xml file.

	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError errorResult = xmlDoc.LoadFile("data/defaultKeyBindings.xml");
	if (errorResult != tinyxml2::XML_SUCCESS) { std::cout << "defaultKeyBindings.xml has failed to load.\n"; }

	tinyxml2::XMLNode* root = xmlDoc.RootElement();
	if (root == nullptr) { std::cout << "defaultKeyBindings.xml root node was not found.\n"; }

	tinyxml2::XMLElement* element = root->FirstChildElement();
	if (element == nullptr) { std::cout << "defaultKeyBindings.xml first child element was not found.\n"; }

	// After retrieving the pointer, we loop through each instance of 'Key' found within the file,
	// reading all of the data and storing it as a const char*. Since const char* are useless in terms
	// of SFML we call the ParseKeys function that converts each const char* into the appropriate 
	// usable enum and stores that data within an instance of KeyData.

	// Lastly we store the newly created KeyData before moving the 'Key' element pointer onto the next
	// instance of 'Key' found within the XML file.

	tinyxml2::XMLElement* data;

	while (element != nullptr) {

		data = element->FirstChildElement("Action");
		if (data == nullptr) { std::cout << "defaultKeyBindings.xml 'Action' not found."; break; }
		const char* action = data->GetText();

		data = element->FirstChildElement("InputType");
		if (data == nullptr) { std::cout << "defaultKeyBindings.xml 'InputType' not found."; break; }
		const char* input = data->GetText();


		data = element->FirstChildElement("KeyCode");
		if (data == nullptr) { std::cout << "defaultKeyBindings.xml 'KeyCode' not found."; break; }
		const char* keycode = data->GetText();

		KeyData key;
		ParseKey(key, input, keycode);

		std::pair<std::string, KeyData> parsedKey;
		parsedKey.first = action;
		parsedKey.second = key;
		defaultKeyBinds.push_back(parsedKey);

		element = element->NextSiblingElement();
	}

	// After storing all of the default key binds we have to repeat the process for the user's customised
	// key binds.

	errorResult = xmlDoc.LoadFile("data/userKeyBindings.xml");
	if (errorResult != tinyxml2::XML_SUCCESS) { std::cout << "userKeyBindings.xml has failed to load.\n"; }

	root = xmlDoc.RootElement();
	if (root == nullptr) { std::cout << "userKeyBindings.xml root node was not found.\n"; }

	element = root->FirstChildElement();
	if (element == nullptr) { std::cout << "userKeyBindings.xml first child element was not found.\n"; }

	while (element != nullptr) {

		data = element->FirstChildElement("Action");
		if (data == nullptr) { std::cout << "userKeyBindings.xml 'Action' not found."; break; }
		const char* action = data->GetText();

		data = element->FirstChildElement("InputType");
		if (data == nullptr) { std::cout << "userKeyBindings.xml 'InputType' not found."; break; }
		const char* input = data->GetText();


		data = element->FirstChildElement("KeyCode");
		if (data == nullptr) { std::cout << "userKeyBindings.xml 'KeyCode' not found."; break; }
		const char* keycode = data->GetText();

		KeyData key;
		ParseKey(key, input, keycode);
		userKeyBinds[action] = key;

		element = element->NextSiblingElement();
	}

}

void KeyBindings::ParseKey(KeyData& key, std::string input, std::string keycode) {

	// The purpose of this function is to convert the const char* gathered from the XML file into the
	// data that is stored within our KeyData struct. This means doing a long list of comparisons in order
	// to figure out that the "E" string within the XML file means we need our instance of
	// KeyData to store the "sf::Keyboard::E" enum for use with SFML's event system.

	// Storing keycode

	key.codeString = keycode;

	// Keyboard Input

	if (input == "Keyboard") {

		// Key Code Q

		if (keycode == "Q") {
			key.keyCode = sf::Keyboard::Q;
			return;
		}

		// Key Code W

		else if (keycode == "W") {
			key.keyCode = sf::Keyboard::W;
			return;
		}

		// Key Code E

		else if (keycode == "E") {
			key.keyCode = sf::Keyboard::E;
			return;
		}

		// Key Code A

		else if (keycode == "A") {
			key.keyCode = sf::Keyboard::A;
			return;
		}

		// Key Code S

		else if (keycode == "S") {
			key.keyCode = sf::Keyboard::S;
			return;
		}

		// Key Code D

		else if (keycode == "D") {
			key.keyCode = sf::Keyboard::D;
			return;
		}

		// Invalid Key Code

		else {
			std::cout << "Invalid Keyboard Key Code:\t" << keycode << "\n";
			return;
		}
	}

	// Mouse Input

	else if (input == "Mouse") {

		// Mouse Button Left

		if (keycode == "Left") {
			key.mouseButton = sf::Mouse::Left;
			return;
		}

		// Mouse Button Right

		else if (keycode == "Right") {
			key.mouseButton = sf::Mouse::Right;
			return;
		}

		// Invalid Mouse Button

		else {
			std::cout << "Invalid Mouse Button Type:\t" << keycode << "\n";
			return;
		}

	}

	// Invalid Input

	else {
		std::cout << "Invalid Input Method:\t" << input << "\n";
		return;
	}
}