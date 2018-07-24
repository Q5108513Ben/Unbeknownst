#include "StateMachine\States\Options.hpp"

#include "XML\KeyBindings.hpp"

OptionsState OptionsState::optionsState;

void OptionsState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	CreateButtons();

	test.setSize(sf::Vector2f(50, 50));
	test.setPosition(sf::Vector2f(150, 150));
	test.setFillColor(sf::Color(sf::Color::Black));
}

void OptionsState::CleanUp() {

	buttonUnfocused();

	for (auto button : buttonMap) {
		guiRef->remove(button.second.getPicture());
	}

	spriteVector.clear();
	textVector.clear();
	buttonMap.clear();
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
			menuView.move(0, sfEvent.mouseWheelScroll.delta * 10);
		}
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
		windowRef->setView(menuView);
		windowRef->draw(test);
		//guiRef->setView(); // This function may allow us to set some of the GUI to render in the new view
		// that will be scrollable.
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

	guiRef->get<tgui::Picture>(buttonName)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonHover"));

	textVector[buttonMap[buttonName].getTextID()].setFillColor(sf::Color(51, 51, 51));
	textVector[buttonMap[buttonName].getTextID()].move(9, 0);

	isFocusingButton = true;
	currentlyFocusedButton = buttonName;
}

void OptionsState::buttonUnfocused() {
	textVector[buttonMap[currentlyFocusedButton].getTextID()].setFillColor(sf::Color(204, 204, 204));
	textVector[buttonMap[currentlyFocusedButton].getTextID()].move(-9, 0);

	guiRef->get<tgui::Picture>(currentlyFocusedButton)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonNormal"));

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

void OptionsState::CreateButtons() {
	// Gameplay Button
	
	uui::TitleScreenButton gameplayButton;
	gameplayButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(gameplayButton.create(uui::Position(54, 663), "Gameplay", uui::Position(72, 657)));

	gameplayButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "GameplayButton");
	gameplayButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	gameplayButton.setLinkedButtons("KeyBindsButton", "VideoButton", " ", " ");

	guiRef->add(gameplayButton.getPicture(), "GameplayButton");
	buttonMap["GameplayButton"] = gameplayButton;

	// Video Button

	uui::TitleScreenButton videoButton;
	videoButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(videoButton.create(uui::Position(54, 684), "Video", uui::Position(72, 678)));

	videoButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "VideoButton");
	videoButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	videoButton.setLinkedButtons("GameplayButton", "UserInterfaceButton", " ", " ");

	guiRef->add(videoButton.getPicture(), "VideoButton");
	buttonMap["VideoButton"] = videoButton;

	// User Interface Button

	uui::TitleScreenButton userInterfaceButton;
	userInterfaceButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(userInterfaceButton.create(uui::Position(54, 705), "User Interface", uui::Position(72, 699)));

	userInterfaceButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "UserInterfaceButton");
	userInterfaceButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	userInterfaceButton.setLinkedButtons("VideoButton", "AudioButton", " ", " ");

	guiRef->add(userInterfaceButton.getPicture(), "UserInterfaceButton");
	buttonMap["UserInterfaceButton"] = userInterfaceButton;

	// Audio Button

	uui::TitleScreenButton audioButton;
	audioButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(audioButton.create(uui::Position(54, 726), "Audio", uui::Position(72, 720)));

	audioButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "AudioButton");
	audioButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	audioButton.setLinkedButtons("UserInterfaceButton", "KeyBindsButton", " ", " ");

	guiRef->add(audioButton.getPicture(), "AudioButton");
	buttonMap["AudioButton"] = audioButton;

	// Key Binds Button

	uui::TitleScreenButton keyBindsButton;
	keyBindsButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(keyBindsButton.create(uui::Position(54, 747), "Key Binds", uui::Position(72, 741)));

	keyBindsButton.getPicture()->connect("MouseEntered", &OptionsState::buttonFocused, &optionsState, "KeyBindsButton");
	keyBindsButton.getPicture()->connect("MouseLeft", &OptionsState::buttonUnfocused, &optionsState);
	keyBindsButton.getPicture()->connect("Clicked", &OptionsState::buttonClicked , &optionsState);
	keyBindsButton.setLinkedButtons("AudioButton", "GameplayButton", " ", " ");

	guiRef->add(keyBindsButton.getPicture(), "KeyBindsButton");
	buttonMap["KeyBindsButton"] = keyBindsButton;
}

void OptionsState::CreateKeyBindsMenu() {

	menuView.reset(sf::FloatRect(0, 0, 720, 810));
	menuView.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
	
	isMenuOpen = true;
}