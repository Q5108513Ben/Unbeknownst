#include "StateMachine\States\TitleScreen.hpp"
#include "StateMachine\States\GameState.hpp"
#include "StateMachine\States\Options.hpp"
#include "UUI\Additional\Position.hpp"

TitleScreenState TitleScreenState::titleScreen;

void TitleScreenState::Initialise(sf::RenderWindow* window, tgui::Gui* gui, StateMachine* machine) {
	windowRef = window;
	guiRef = gui;

	CreateSprite("TitleScreen_Background");

	titleScreenWidgets.loadFromFile("images/TitleScreen_Theme.png");

	sf::Texture buttonNormal = uui::Texture::create(titleScreenWidgets, sf::IntRect(2, 2, 55, 7));
	uui::ResourceManager::Instance()->addTexture("ButtonNormal", buttonNormal);
	sf::Texture buttonHover = uui::Texture::create(titleScreenWidgets, sf::IntRect(2, 11, 55, 7));
	uui::ResourceManager::Instance()->addTexture("ButtonHover", buttonHover);

	CreateButtons(machine);

}

void TitleScreenState::CleanUp() {

}

void TitleScreenState::Pause() {
	guiRef->get("NewGameButton")->hide();
	guiRef->get("ContinueButton")->hide();
	guiRef->get("LoadGameButton")->hide();
	guiRef->get("ExtrasButton")->hide();
	guiRef->get("OptionsButton")->hide();
}

void TitleScreenState::Resume() {
	guiRef->get("NewGameButton")->show();
	guiRef->get("ContinueButton")->show();
	guiRef->get("LoadGameButton")->show();
	guiRef->get("ExtrasButton")->show();
	guiRef->get("OptionsButton")->show();
}

void TitleScreenState::HandleEvent(StateMachine* machine, sf::Event sfEvent) {

	switch (sfEvent.type) {

	case sf::Event::KeyReleased:

		switch (sfEvent.key.code) {

		case sf::Keyboard::Escape:
			if (!subStateSelected) {
				machine->Quit();
			}
			else {
				removeSubState();
			}
			break;
		}

		if (!subStateSelected) {
			if (sfEvent.key.code == sf::Keyboard::W) {
				changeSelectedButton(0);
			}

			else if (sfEvent.key.code == sf::Keyboard::S) {
				changeSelectedButton(1);
			}

			else if (sfEvent.key.code == sf::Keyboard::A) {
				changeSelectedButton(2);
			}

			else if (sfEvent.key.code == sf::Keyboard::D) {
				changeSelectedButton(3);
			}
		}

		if (!subStateSelected && isFocusingButton) {
			if (sfEvent.key.code == sf::Keyboard::Return) {
				buttonClicked(machine);
			}
		}

	break;

	}

	if (subStateSelected) {
		switch (currentlySelectedSubState) {
		case LoadGame:
			break;
		case Extras:
			break;
		case Options:
			OptionsState::Instance()->HandleEvent(machine, sfEvent);
			break;
		}
	}
}

void TitleScreenState::Update(StateMachine* machine) {
	if (!subStateSelected && isFocusingButton ) {
		std::cout << currentlyFocusedButton << std::endl;
	}
	
}

void TitleScreenState::Render() {
	
	for (auto sprite : spriteVector) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}

	if (!subStateSelected) {
		for (auto text : textVector) {
			windowRef->draw(text);
		}
	}
	else {

		switch (currentlySelectedSubState) {
		case LoadGame:
			break;
		case Extras:
			break;
		case Options:
			OptionsState::Instance()->Render();
			break;
		}
	}
}

void TitleScreenState::buttonFocused(std::string buttonName) {
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

void TitleScreenState::buttonUnfocused() {
	textVector[buttonMap[currentlyFocusedButton].getTextID()].setFillColor(sf::Color(204, 204, 204));
	textVector[buttonMap[currentlyFocusedButton].getTextID()].move(-9, 0);

	guiRef->get<tgui::Picture>(currentlyFocusedButton)->setTexture(uui::ResourceManager::Instance()->getTexture("ButtonNormal"));

	isFocusingButton = false;
}

void TitleScreenState::buttonClicked(StateMachine* machine) {
	if (currentlyFocusedButton == "NewGameButton") {
		machine->PushState(GameState::Instance());
	}
	else if (currentlyFocusedButton == "ContinueButton") {
		
	}
	else if (currentlyFocusedButton == "LoadGameButton") {
		
	}
	else if (currentlyFocusedButton == "ExtrasButton") {
		
	}
	else if (currentlyFocusedButton == "OptionsButton") {
		changeSubState(SubState::Options);
	}
}

void TitleScreenState::changeSelectedButton(unsigned int direction) {
	if (!isFocusingButton) {
		buttonFocused("NewGameButton");
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

void TitleScreenState::changeSubState(SubState state) {
	subStateSelected = true;
	Pause();
}

void TitleScreenState::removeSubState() {
	switch (currentlySelectedSubState) {
	case LoadGame:
		break;
	case Extras:
		break;
	case Options:
		OptionsState::Instance()->CleanUp();
		break;
	}
	
	subStateSelected = false;
	Resume();
}



void TitleScreenState::CreateSprite(std::string fileName) {
	sf::Texture texture = uui::Texture::create(fileName + ".png");
	uui::ResourceManager::Instance()->addTexture(fileName, texture);
	sf::Sprite sprite = uui::Sprite::create(uui::ResourceManager::Instance()->getTexture(fileName));
	spriteVector.push_back(sprite);
}

void TitleScreenState::CreateButtons(StateMachine* machine) {
	// New Game Button

	uui::TitleScreenButton newgameButton;
	newgameButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(newgameButton.create(uui::Position(54, 663), "New Game", uui::Position(72, 657)));

	newgameButton.getPicture()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, "NewGameButton");
	newgameButton.getPicture()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen);
	newgameButton.getPicture()->connect("Clicked", [=]() { machine->PushState(GameState::Instance()); });
	newgameButton.setLinkedButtons("OptionsButton", "ContinueButton", " ", " ");

	guiRef->add(newgameButton.getPicture(), "NewGameButton");
	buttonMap["NewGameButton"] = newgameButton;

	// Continue Button

	uui::TitleScreenButton continueButton;
	continueButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(continueButton.create(uui::Position(54, 684), "Continue", uui::Position(72, 678)));

	continueButton.getPicture()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, "ContinueButton");
	continueButton.getPicture()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen);
	continueButton.getPicture()->connect("Clicked", [=]() { machine->PushState(GameState::Instance()); });
	continueButton.setLinkedButtons("NewGameButton", "LoadGameButton", " ", " ");

	guiRef->add(continueButton.getPicture(), "ContinueButton");
	buttonMap["ContinueButton"] = continueButton;

	// Load Game Button

	uui::TitleScreenButton loadgameButton;
	loadgameButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(loadgameButton.create(uui::Position(54, 705), "Load Game", uui::Position(72, 699)));

	loadgameButton.getPicture()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, "LoadGameButton");
	loadgameButton.getPicture()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen);
	loadgameButton.getPicture()->connect("Clicked", [=]() { machine->PushState(GameState::Instance()); });
	loadgameButton.setLinkedButtons("ContinueButton", "ExtrasButton", " ", " ");

	guiRef->add(loadgameButton.getPicture(), "LoadGameButton");
	buttonMap["LoadGameButton"] = loadgameButton;

	// Extras Button

	uui::TitleScreenButton extrasButton;
	extrasButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(extrasButton.create(uui::Position(54, 726), "Extras", uui::Position(72, 720)));

	extrasButton.getPicture()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, "ExtrasButton");
	extrasButton.getPicture()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen);
	extrasButton.getPicture()->connect("Clicked", [=]() { machine->PushState(GameState::Instance()); });
	extrasButton.setLinkedButtons("LoadGameButton", "OptionsButton", " ", " ");

	guiRef->add(extrasButton.getPicture(), "ExtrasButton");
	buttonMap["ExtrasButton"] = extrasButton;

	// Options Button

	uui::TitleScreenButton optionsButton;
	optionsButton.setIndex((unsigned int)textVector.size(), (unsigned int)buttonMap.size());
	textVector.push_back(optionsButton.create(uui::Position(54, 747), "Options", uui::Position(72, 741)));

	optionsButton.getPicture()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, "OptionsButton");
	optionsButton.getPicture()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen);
	optionsButton.getPicture()->connect("Clicked", &TitleScreenState::changeSubState, &titleScreen, SubState::Options);
	optionsButton.setLinkedButtons("ExtrasButton", "NewGameButton", " ", " ");

	guiRef->add(optionsButton.getPicture(), "OptionsButton");
	buttonMap["OptionsButton"] = optionsButton;

}