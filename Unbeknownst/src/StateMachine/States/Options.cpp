#include "StateMachine\States\Options.hpp"

OptionsState OptionsState::optionsState;

void OptionsState::Initialise(sf::RenderWindow* window, tgui::Gui* gui) {
	windowRef = window;
	guiRef = gui;

	CreateButtons();
}

void OptionsState::CleanUp() {
	// Here we need to remove all the buttons we created when initialising.
}

void OptionsState::Pause() {

}

void OptionsState::Resume() {
	// Resume and Pause probably wont get used unless we have a substate of the substate.
	// The keybindings would probably need its own state since there are so many buttons and 
	// we would need a method of preventing the user from interacting with anything when 
	// changing key binds.
}

void OptionsState::HandleEvent(StateMachine* machine, sf::Event sfEvent) {

}

void OptionsState::Update(StateMachine* machine) {

}

void OptionsState::Render() {

	for (auto sprite : spriteVector) {
		sprite.scale(3, 3);
		windowRef->draw(sprite);
	}

}

void OptionsState::CreateButtons() {

}