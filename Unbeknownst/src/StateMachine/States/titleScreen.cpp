#include "StateMachine\States\titleScreen.hpp"

TitleScreenState TitleScreenState::titleScreen;

void TitleScreenState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;
}

void TitleScreenState::CleanUp() {

}

void TitleScreenState::Pause() {

}

void TitleScreenState::Resume() {

}

void TitleScreenState::HandleEvent(StateMachine* machine, sf::Event event) {

}

void TitleScreenState::Update(StateMachine* machine) {

}

void TitleScreenState::Render(StateMachine* machine) {

}