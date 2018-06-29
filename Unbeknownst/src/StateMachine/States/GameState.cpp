#include "StateMachine\States\GameState.hpp"

GameState GameState::gameState;

void GameState::Initialise(sf::RenderWindow* window, tgui::Gui* gui, StateMachine* machine) {
	windowRef = window;
	guiRef = gui;

	//Here we need something that determines whether we are initialising from New Game or Continue 
	//game, since continue game will require us to load a save.
}

void GameState::CleanUp() {

}

void GameState::Pause() {

}

void GameState::Resume() {

}

void GameState::HandleEvent(StateMachine* machine, sf::Event sfEvent) {

}

void GameState::Update(StateMachine* machine) {

}

void GameState::Render() {

}