#include "StateMachine\States\Options.hpp"

#include "XML\KeyBindings.hpp"

OptionsState OptionsState::optionsState;

void OptionsState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	CreateButtons();
}

void OptionsState::CleanUp() {
	
	if (isMenuOpen) {
		RemoveMenu();
	}
	
	for (auto button : buttonMap) {
		guiRef->remove(button.second.getPicture());
	}

	spriteVector.clear();
	textVector.clear();
	buttonMap.clear();

	isFocusingButton = false;
}

void OptionsState::Pause() {

}

void OptionsState::Resume() {
	
}

void OptionsState::HandleEvent(StateMachine* machine, sf::Event sfEvent) {

	switch (sfEvent.type) {

	case sf::Event::KeyPressed:

		if (CompareKey(KeyBindings::Instance()->GetKey("Move - Up"), sfEvent.key.code)) {
			changeSelectedButton(0);
		}
		else if (CompareKey(KeyBindings::Instance()->GetKey("Move - Down"), sfEvent.key.code)) {
			changeSelectedButton(1);
		}
		else if (CompareKey(KeyBindings::Instance()->GetKey("Move - Left"), sfEvent.key.code)) {
			changeSelectedButton(2);
		}
		else if (CompareKey(KeyBindings::Instance()->GetKey("Move - Right"), sfEvent.key.code)) {
			changeSelectedButton(3);
		}

	}

	if (isMenuOpen) {
		if (sfEvent.type == sf::Event::MouseWheelScrolled) {
			menuView.move(0, -sfEvent.mouseWheelScroll.delta * 18);
		}

		keyBindGUI.handleEvent(sfEvent);

	}
}

void OptionsState::Update(StateMachine* machine) {
	
}

void OptionsState::Render() {

	for (auto sprite : spriteVector) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}

	for (auto text : textVector) {
		windowRef->draw(text);
	}

	if (isMenuOpen) {

		keyBindGUI.setView(menuView);
		keyBindGUI.draw();

		windowRef->setView(menuView);
		
		for (auto text : textVectorKeyBind) {
			windowRef->draw(text);
		}

		windowRef->setView(windowRef->getDefaultView());
	}

}

void OptionsState::buttonFocused(std::string buttonName) {
	if (isFocusingButton && currentlyFocusedButton == buttonName) {
		return;
	}

	if (isFocusingButton) {
		buttonUnfocused();
	}

	guiRef->get<tgui::Picture>(buttonName)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonHover_TitleScreen"));

	textVector[buttonMap[buttonName].getTextID()].setFillColor(sf::Color(51, 51, 51));
	textVector[buttonMap[buttonName].getTextID()].move(9, 0);

	isFocusingButton = true;
	currentlyFocusedButton = buttonName;
}

void OptionsState::buttonUnfocused() {
	textVector[buttonMap[currentlyFocusedButton].getTextID()].setFillColor(sf::Color(204, 204, 204));
	textVector[buttonMap[currentlyFocusedButton].getTextID()].move(-9, 0);

	guiRef->get<tgui::Picture>(currentlyFocusedButton)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonNormal_TitleScreen"));

	isFocusingButton = false;
}

void OptionsState::buttonClicked() {
	if (currentlyFocusedButton == "GameplayButton") {
		
	}
	else if (currentlyFocusedButton == "VideoButton") {

	}
	else if (currentlyFocusedButton == "UserInterfaceButton") {

	}
	else if (currentlyFocusedButton == "AudioButton") {

	}
	else if (currentlyFocusedButton == "KeyBindsButton") {
		if (!isMenuOpen) {
			CreateKeyBindsMenu();
		}
	}
}

void OptionsState::changeSelectedButton(unsigned int direction) {
	if (!isFocusingButton) {
		buttonFocused("GameplayButton");
		return;
	}

	std::string nextButton{ " " };

	switch (direction) {
	case 0: // UP
		nextButton = buttonMap[currentlyFocusedButton].getNextUp();
		break;
	case 1: // DOWN
		nextButton = buttonMap[currentlyFocusedButton].getNextDown();
		break;
	case 2: // LEFT
		nextButton = buttonMap[currentlyFocusedButton].getNextLeft();
		break;
	case 3: // RIGHT
		nextButton = buttonMap[currentlyFocusedButton].getNextRight();
		break;
	}

	if (nextButton == " ") {
		return;
	}
	else {
		buttonUnfocused();
		buttonFocused(nextButton);
	}
}

void OptionsState::CreateSprite(std::string fileName, uui::Position pos) {
	sf::Texture texture = uui::Texture::create(fileName + ".png");
	uui::ResourceManager::Instance()->addTexture(fileName, texture);
	sf::Sprite sprite = uui::Sprite::create(uui::ResourceManager::Instance()->getTexture(fileName), pos);
	spriteVector.push_back(sprite);
}

void OptionsState::RemoveMenu() {

	switch (currentlyOpenedMenu) {
	case KeyBind:

		for (auto button : buttonMapKeyBind) {
			keyBindGUI.remove(button.second.getPicture());
		}

		spriteVector.clear();
		textVectorKeyBind.clear();
		buttonMapKeyBind.clear();

		isFocusingKeyBind = false;
		isSelectingKeyBind = false;

		break;
	}

	isMenuOpen = false;

}

void OptionsState::CreateButtons() {
	// Gameplay Button
	
	uui::TitleScreenButton gameplayButton;
	gameplayButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(gameplayButton.create(uui::Position(54, 663), "Gameplay", uui::Position(72, 657), "ButtonNormal_TitleScreen"));

	gameplayButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "GameplayButton");
	gameplayButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	gameplayButton.setLinkedButtons("KeyBindsButton", "VideoButton", " ", " ");

	guiRef->add(gameplayButton.getPicture(), "GameplayButton");
	buttonMap["GameplayButton"] = gameplayButton;

	// Video Button

	uui::TitleScreenButton videoButton;
	videoButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(videoButton.create(uui::Position(54, 684), "Video", uui::Position(72, 678), "ButtonNormal_TitleScreen"));

	videoButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "VideoButton");
	videoButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	videoButton.setLinkedButtons("GameplayButton", "UserInterfaceButton", " ", " ");

	guiRef->add(videoButton.getPicture(), "VideoButton");
	buttonMap["VideoButton"] = videoButton;

	// User Interface Button

	uui::TitleScreenButton userInterfaceButton;
	userInterfaceButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(userInterfaceButton.create(uui::Position(54, 705), "User Interface", uui::Position(72, 699), "ButtonNormal_TitleScreen"));

	userInterfaceButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "UserInterfaceButton");
	userInterfaceButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	userInterfaceButton.setLinkedButtons("VideoButton", "AudioButton", " ", " ");

	guiRef->add(userInterfaceButton.getPicture(), "UserInterfaceButton");
	buttonMap["UserInterfaceButton"] = userInterfaceButton;

	// Audio Button

	uui::TitleScreenButton audioButton;
	audioButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(audioButton.create(uui::Position(54, 726), "Audio", uui::Position(72, 720), "ButtonNormal_TitleScreen"));

	audioButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "AudioButton");
	audioButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	audioButton.setLinkedButtons("UserInterfaceButton", "KeyBindsButton", " ", " ");

	guiRef->add(audioButton.getPicture(), "AudioButton");
	buttonMap["AudioButton"] = audioButton;

	// Key Binds Button

	uui::TitleScreenButton keyBindsButton;
	keyBindsButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(keyBindsButton.create(uui::Position(54, 747), "Key Binds", uui::Position(72, 741), "ButtonNormal_TitleScreen"));

	keyBindsButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "KeyBindsButton");
	keyBindsButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	keyBindsButton.getPicture()->connect("Clicked", &OptionsState::buttonClicked , &optionsState);
	keyBindsButton.setLinkedButtons("AudioButton", "GameplayButton", " ", " ");

	guiRef->add(keyBindsButton.getPicture(), "KeyBindsButton");
	buttonMap["KeyBindsButton"] = keyBindsButton;
}

void OptionsState::CreateKeyBindsMenu() {

	// Create the necessary sprites that will be used whilst the Key Binds menu is open, the reason we have
	// created another std::vector to store more sprites is because some sprites / buttons etc. will need 
	// to be rendered to a different sf::View.

	CreateSprite("TitleScreen_KeyBinds", uui::Position(222 * 3, 16 * 3));
	
	// Setting up the view. The width and height of the view that we want is 222x221, we multiply this by
	// the scale. The Viewport works similarly except it uses %'s rather than hard values and we also set
	// the position of the view relative to the window here. Obviously it works on a range of 0-1 so to 
	// get the % you just multiply by 100.

	menuView.reset(sf::FloatRect(0, 0, 222 * 3, 221 * 3));
	menuView.setViewport(sf::FloatRect(0.4771f, 0.0926f, 0.4625f, 0.8175f));

	keyBindGUI.setWindow(*windowRef);
	
	// Drawing all the text. This text is gotten from our KeyData map and is the 'Key' to each item in the 
	// map. The text is not going to do anything special however we need to make sure to draw() it to
	// the view that will be used for the keybinds as we need to be able to scroll this inforamtion up
	// and down.

	// We also need to create the buttons that will sit beside the text, this button will display the 
	// currently bound key that is also retrieved from our KeyData map, however this information will be 
	// pulled from the user's key binds rather than the default key binds.

	float xPosText{ 53 * 3 };
	float yPosIncrementText{ 0 };

	float xPosButton = 123 * 3;
	float xPosButtonText = 169 * 3;
	float yPosIncrementButton =  2 * 3;
	int buttonNo{ 0 };

	for (auto key : KeyBindings::Instance()->GetDefaultKeys()) {

		// Creating action name text

		sf::Text sfText;

		sfText.setFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
		sfText.setCharacterSize(24);
		sfText.setFillColor(sf::Color(204, 204, 204));
		sfText.setString(key.first);
		sfText.setPosition(xPosText - (sfText.getLocalBounds().width / 2), yPosIncrementText);

		

		textVectorKeyBind.push_back(sfText);

		// Creating key bind display button

		uui::TitleScreenButton uuiButton;
		uuiButton.setIndex((unsigned int)textVectorKeyBind.size(), (unsigned int)buttonMapKeyBind.size());

		std::string buttonName{ "KeyBind" + std::to_string(buttonNo) };
		textVectorKeyBind.push_back(uuiButton.create(uui::Position(xPosButton, yPosIncrementButton), key.second.codeString, uui::Position(xPosButtonText, yPosIncrementText), "ButtonNormal_KeyBinds"));
		
		textVectorKeyBind[uuiButton.getTextID()].setPosition(xPosButtonText - (textVectorKeyBind[uuiButton.getTextID()].getLocalBounds().width / 2), yPosIncrementText);

		uuiButton.getPicture()->connect("MouseEntered", &OptionsState::keyBindFocused, &optionsState, buttonName);
		uuiButton.getPicture()->connect("MouseLeft", &OptionsState::keyBindUnfocused, &optionsState);
		uuiButton.getPicture()->connect("Clicked", &OptionsState::keyBindSelected, &optionsState, buttonName);

		keyBindGUI.add(uuiButton.getPicture(), buttonName);
		buttonMapKeyBind[buttonName] = uuiButton;

		yPosIncrementText += 10 * 3;
		yPosIncrementButton += 10 * 3;
		buttonNo++;

	}

	isMenuOpen = true;
	currentlyOpenedMenu = KeyBind;

}

void OptionsState::keyBindFocused(std::string buttonName) {

	if (isFocusingKeyBind && currentlyFocusedButton == buttonName) {
		return;
	}

	if (isSelectingKeyBind && currentlySelectedKeyBind == buttonName) {
		return;
	}

	if (isFocusingKeyBind) {
		keyBindUnfocused();
	}

	keyBindGUI.get<tgui::Picture>(buttonName)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonHover_KeyBinds"));

	textVectorKeyBind[buttonMapKeyBind[buttonName].getTextID()].setFillColor(sf::Color(51, 51, 51));

	isFocusingKeyBind = true;
	currentlyFocusedButton = buttonName;
	currentlyFocusedKeyBind = buttonName;

}

void OptionsState::keyBindUnfocused() {

	if (isSelectingKeyBind && currentlySelectedKeyBind == currentlyFocusedKeyBind) {
		return;
	}

	textVectorKeyBind[buttonMapKeyBind[currentlyFocusedKeyBind].getTextID()].setFillColor(sf::Color(204, 204, 204));

	keyBindGUI.get<tgui::Picture>(currentlyFocusedKeyBind)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonNormal_KeyBinds"));

	isFocusingKeyBind = false;

}

void OptionsState::keyBindSelected(std::string buttonName) {

	if (isSelectingKeyBind && currentlySelectedKeyBind == buttonName) {
		return;
	}

	if (isSelectingKeyBind) {
		keyBindUnselected();
	}

	keyBindGUI.get<tgui::Picture>(buttonName)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonSelected_KeyBinds"));

	isSelectingKeyBind = true;
	currentlySelectedKeyBind = buttonName;

}

void OptionsState::keyBindUnselected() {

	keyBindGUI.get<tgui::Picture>(currentlySelectedKeyBind)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonNormal_KeyBinds"));

	textVectorKeyBind[buttonMapKeyBind[currentlySelectedKeyBind].getTextID()].setFillColor(sf::Color(204, 204, 204));

	isSelectingKeyBind = false;

}