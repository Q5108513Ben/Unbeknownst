#include "Managers\uiManager.hpp"
#include "UUI\UUI.hpp"

UIManager UIManager::uiManager;

void UIManager::LoadBaseUI(sf::RenderWindow* window, tgui::Gui* gui, StateMachine* machine) {
	windowPtr = window;
	guiPtr = gui;

	sf::Font font;
	font.loadFromFile("UnbeknownstStnd.ttf");
	uui::ResourceManager::Instance()->addFont("UnbeknownstStnd", font);

	tgui::Theme::Ptr theme = tgui::Theme::create("images/TitleScreen_Theme.txt");
	uui::ResourceManager::Instance()->addTheme("TitleScreen", theme);

	auto toolbar = tgui::Picture::create();
	toolbar->setSize(1440, 24);
	guiPtr->add(toolbar, "Toolbar");
	toolbar->connect("MousePressed", &UIManager::EnableMoveableWindow, &uiManager);
	toolbar->connect("MouseReleased", [&]() {grabbedWindow = false; });

}

void UIManager::Render() {
	if (grabbedWindow) {
		windowPtr->setPosition(sf::Mouse::getPosition() + grabbedOffset);
	}
}

void UIManager::EnableMoveableWindow() {
	grabbedOffset = windowPtr->getPosition() - sf::Mouse::getPosition();
	grabbedWindow = true;
}