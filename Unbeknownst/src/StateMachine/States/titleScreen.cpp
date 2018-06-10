#include "StateMachine\States\TitleScreen.hpp"
#include "UUI\UUI.hpp"
#include "UUI\Additional\Position.hpp"

TitleScreenState TitleScreenState::titleScreen;

void TitleScreenState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	CreateSprite("TitleScreen_Background");
	CreateButtons();

}

void TitleScreenState::CleanUp() {

}

void TitleScreenState::Pause() {

}

void TitleScreenState::Resume() {

}

void TitleScreenState::HandleEvent(StateMachine* machine, sf::Event sfEvent) {

	switch (sfEvent.type) {

	case sf::Event::KeyReleased: 

			switch (sfEvent.key.code) {

			case sf::Keyboard::Escape:
				machine->Quit();
				break;

			case sf::Keyboard::S:
				
				break;
			}

			if (isFocusingButton) {
				if (sfEvent.key.code == sf::Keyboard::Return) {
					std::cout << "Pressed button: " << currentlyFocusedButton << std::endl;
				}
			}
			
		break;
	}
}

void TitleScreenState::Update(StateMachine* machine) {
	if (isFocusingButton) {
		std::cout << currentlyFocusedButton << std::endl;
	}
	
}

void TitleScreenState::Render(StateMachine* machine) {
	
	for (auto sprite : spriteVector) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}

	for (auto text : textVector) {
		windowRef->draw(text);
	}
}

void TitleScreenState::buttonFocused(unsigned int textIndex, unsigned int buttonID) {
	if (isFocusingButton && currentlyFocusedButton == buttonID) {
		return;
	}
	
	textVector[textIndex].setFillColor(sf::Color(51, 51, 51));
	textVector[textIndex].move(9, 0);

	isFocusingButton = true;
	currentlyFocusedButton = buttonID;
}

void TitleScreenState::buttonUnfocused(unsigned int textIndex) {
	textVector[textIndex].setFillColor(sf::Color(204, 204, 204));
	textVector[textIndex].move(-9, 0);

	isFocusingButton = false;
}

void TitleScreenState::buttonClicked() {
	std::cout << "Button Clicked";
}

void TitleScreenState::CreateSprite(std::string fileName) {
	sf::Texture texture = uui::Texture::create(fileName + ".png");
	uui::ResourceManager::Instance()->addTexture(fileName, texture);
	sf::Sprite sprite = uui::Sprite::create(uui::ResourceManager::Instance()->getTexture(fileName));
	spriteVector.push_back(sprite);
}

void TitleScreenState::CreateButtons() {
	// New Game Button

	uui::Button newgameButton(uui::ResourceManager::Instance()->getTheme("TitleScreen"), uui::Position(54, 663), "New Game", uui::Position(72, 657));
	newgameButton.setTextFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
	newgameButton.setTextColour(sf::Color(204, 204, 204));

	newgameButton.getButton()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, 0, 0);
	newgameButton.getButton()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen, 0);
	newgameButton.getButton()->connect("Clicked", &TitleScreenState::buttonClicked, &titleScreen);

	guiRef->add(newgameButton.getButton(), "Button0");
	textVector.push_back(newgameButton.getText());

	// Continue Button

	uui::Button continueButton(uui::ResourceManager::Instance()->getTheme("TitleScreen"), uui::Position(54, 684), "Continue", uui::Position(72, 678));
	continueButton.setTextFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
	continueButton.setTextColour(sf::Color(204, 204, 204));

	continueButton.getButton()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, 1, 1);
	continueButton.getButton()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen, 1);
	continueButton.getButton()->connect("Clicked", &TitleScreenState::buttonClicked, &titleScreen);

	guiRef->add(continueButton.getButton(), "Button1");
	textVector.push_back(continueButton.getText());

	// Load Game Button

	uui::Button loadgameButton(uui::ResourceManager::Instance()->getTheme("TitleScreen"), uui::Position(54, 705), "Load Game", uui::Position(72, 699));
	loadgameButton.setTextFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
	loadgameButton.setTextColour(sf::Color(204, 204, 204));

	loadgameButton.getButton()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, 2, 2);
	loadgameButton.getButton()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen, 2);
	loadgameButton.getButton()->connect("Clicked", &TitleScreenState::buttonClicked, &titleScreen);

	guiRef->add(loadgameButton.getButton(), "Button2");
	textVector.push_back(loadgameButton.getText());

	// Extras Button

	uui::Button extrasButton(uui::ResourceManager::Instance()->getTheme("TitleScreen"), uui::Position(54, 726), "Extras", uui::Position(72, 720));
	extrasButton.setTextFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
	extrasButton.setTextColour(sf::Color(204, 204, 204));

	extrasButton.getButton()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, 3, 3);
	extrasButton.getButton()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen, 3);
	extrasButton.getButton()->connect("Clicked", &TitleScreenState::buttonClicked, &titleScreen);

	guiRef->add(extrasButton.getButton(), "Button3");
	textVector.push_back(extrasButton.getText());

	// Options Button

	uui::Button optionsButton(uui::ResourceManager::Instance()->getTheme("TitleScreen"), uui::Position(54, 747), "Options", uui::Position(72, 741));
	optionsButton.setTextFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
	optionsButton.setTextColour(sf::Color(204, 204, 204));

	optionsButton.getButton()->connect("MouseEntered", &TitleScreenState::buttonFocused, &titleScreen, 4, 4);
	optionsButton.getButton()->connect("MouseLeft", &TitleScreenState::buttonUnfocused, &titleScreen, 4);
	optionsButton.getButton()->connect("Clicked", &TitleScreenState::buttonClicked, &titleScreen);

	guiRef->add(optionsButton.getButton(), "Button4");
	textVector.push_back(optionsButton.getText());
}