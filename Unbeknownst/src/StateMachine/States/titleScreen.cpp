#include "StateMachine\States\TitleScreen.hpp"
#include "StateMachine\States\GameState.hpp"
#include "StateMachine\States\Options.hpp"

#include "UUI\Additional\Position.hpp"
#include "XML\KeyBindings.hpp"

TitleScreenState TitleScreenState::titleScreen;

void TitleScreenState::Initialise(sf::RenderWindow* window, tgui::Gui* gui, StateMachine* machine) {
	windowRef = window;
	guiRef = gui;

	KeyBindings::Instance()->InitialiseKeyBinds();

	CreateSprite("TitleScreen_Background");

	titleScreenWidgets.loadFromFile("images/TitleScreen_Theme.png");

	sf::Texture buttonNormal = uui::Texture::create(titleScreenWidgets, sf::IntRect(2, 2, 55, 7));
	uui::ResourceManager::Instance()->addTexture("ButtonNormal", buttonNormal);
	sf::Texture buttonHover = uui::Texture::create(titleScreenWidgets, sf::IntRect(2, 11, 55, 7));
	uui::ResourceManager::Instance()->addTexture("ButtonHover", buttonHover);

	CreateButtons(machine);

}

void TitleScreenState::CleanUp() {

	// CleanUp() will be called whenever we are removing a State from the StateMachine.

	// CleanUp() will delete any and all data that is stored withing the class, most of which is stored
	// in std::vector's or std::unordered_map's. TGUI's widgets aren't stored manually as they are 
	// automatically added to the tgui::Gui when they are created, so we need to make sure to remove
	// those from the GUI as well.

}

void TitleScreenState::Pause() {

	// The Pause() function is generally called whenever we leave this state and move onto another one,
	// there are some execptions, for example when we move into the GameState we no longer need to store
	// the TitleScreen so CleanUp() would be called instead. Whenever we move to one of the TitleScreen's
	// sub-states we would also call Pause().

	// Pause() simply hides all buttons that we have created, since we are likely to Resume() shortly
	// after we don't want to delete anything just yet, so we just hide it.

	guiRef->get("NewGameButton")->hide();
	guiRef->get("ContinueButton")->hide();
	guiRef->get("LoadGameButton")->hide();
	guiRef->get("ExtrasButton")->hide();
	guiRef->get("OptionsButton")->hide();
}

void TitleScreenState::Resume() {

	// Resume() is called whenever we return to this state and this state was previously paused, if the
	// state has been deleted then we would just Initialise() it again since there is technically nothing
	// to resume.

	// Resume() basically undoes all of the things that Pause() did when we originally called that.

	guiRef->get("NewGameButton")->show();
	guiRef->get("ContinueButton")->show();
	guiRef->get("LoadGameButton")->show();
	guiRef->get("ExtrasButton")->show();
	guiRef->get("OptionsButton")->show();
}

void TitleScreenState::HandleEvent(StateMachine* machine, sf::Event sfEvent) {
	
	// The HandleEvent() function is where we take the sf::Event retrieved from SFML and make our key
	// presses do something. 

	// We begin with a switch statement that uses the sf::Event's type, this allows us to specify the 
	// type of event we want to occur in order to provoke our functions. For the most part we will be
	// using sf::Event::KeyPressed and sf::Event::MouseButtonPresses, however they also have Released
	// types that can be useful if you don't want to be able to hold down the button for repeated 
	// function calls. There are many other sf::Event types but they won't be seen as often.


	switch (sfEvent.type) {

	case sf::Event::KeyPressed:

		// Here we do a check where we are specifying the sf::Keyboard::Escape key. We want to hard-code
		// this key as it is expected by the users to have the same functionality in most programs, this
		// program is no exception so the Escape will always close the game whilst on the title screen,
		// if we are within one of the menus then Escape will simply go back to the previous menu.

		if (sfEvent.key.code == sf::Keyboard::Escape) {

			if (!subStateSelected) {
				machine->Quit();
				return;
			}
			else {
				removeSubState();
				break;
			}
		}

		// Next is functionality specific to the TitleScreenState. I decided to introduce the idea of 
		// sub-states since it is beneficial to split up the code rather than have it all in one file,
		// however I still needed to maintain certain data. For example whilst on the title screen we may
		// want some music to play, if the menus were their own states then the music would stop and start
		// everytime we changed states, with sub-states we can keep the music playing whilst passing
		// control over to another menu.

		// So this is where our key binds come into play, instead of hard-coding the values like the 
		// Escape key, we want to allow the user to rebind all of their keys for movement or interacting
		// with buttons etc. Because of this I have created my own KeyData class, we then just compare
		// this class to the sf::Event's key data and if it matches then we execute the specified code.

		if (!subStateSelected) {

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

			if (isFocusingButton) {
				if (CompareKey(KeyBindings::Instance()->GetKey("Interact"), sfEvent.key.code)) {
					buttonClicked(machine);
				}
			}
		}
	}

	// Lastly we check to see if the user has selected one of the buttons that move us from the Title
	// Screen to one of it's sub-states. If it has then we need to pass control over to it, so we simply
	// call the sub-states HandleEvent() function that functions exactly the same as this one, passing
	// over the StateMachine and the sf::Event that was originally passed into this function.

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
	if (subStateSelected) {
		switch (currentlySelectedSubState) {
		case Options:
			OptionsState::Instance()->Update(machine);
			break;
		}
	}
}

void TitleScreenState::Render() {
	
	// Fairly self explanatory, here we are rendering all of the sprites we have stored within the class.
	// Right now it is hard-coded to scale all sprites however this will eventually be a variable that
	// changes based on the player's selected resolution, obviously higher resoulutions will require
	// higher scaling.

	// Similarly to the HandleEvent() function, if we are currently within a sub-state then we need to
	// call the Render() function of the sub-state so that it can handle it's own rendering.

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
		buttonFocused("ContinueButton");
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
	Pause();
	
	switch (state) {
	case LoadGame:
		break;
	case Extras:
		break;
	case Options:
		OptionsState::Instance()->Initialise(windowRef, guiRef);
		break;
	}
	
	subStateSelected = true;
	currentlySelectedSubState = state;
	
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