#include "StateMachine\stateMachine.hpp"
#include "StateMachine\virtualState.hpp"
#include "UUI\ResourceManager.hpp"
#include "Managers\uiManager.hpp"

StateMachine::StateMachine() : window(sf::VideoMode(1440, 810), "Unbeknownst", sf::Style::None),
							   gui(window) {
	windowPtr = &window;
	guiPtr = &gui;
	this->Initialise();
}

void StateMachine::Initialise() {
	isRunning = true;
	UIManager::Instance()->LoadBaseUI(windowPtr, guiPtr, this);

	fps.setFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
	fps.setCharacterSize(24);
	fps.setFillColor(sf::Color(51, 51, 51));
	fps.setPosition(12, 0);
	fps.setString(" ");

}

void StateMachine::CleanUp() {
	while (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
	}

	currentState = nullptr;
	previousState = nullptr;
}

void StateMachine::PushState(State* state) {
	if (CheckState(state)) {
		SwitchState(state);
		return;
	}

	if (!states.empty()) {
		currentState->Pause();
		previousState = currentState;
	}

	states.push_back(state);
	states.back()->Initialise(windowPtr, guiPtr, this);
	currentState = state;
}

void StateMachine::SwitchState(State* state) {
	if (!CheckState(state)) {
		return;
	}

	if (state != currentState) {
		currentState->Pause();
		previousState = currentState;

		state->Resume();
		currentState = state;
	}
}

void StateMachine::PopState() {
	if (!states.empty()) {
		states.back()->CleanUp();
		states.pop_back();
		State* tempCurrState = currentState;
		currentState = nullptr;

		if (!states.empty()) {
			currentState = previousState;
			previousState = tempCurrState;
			previousState->Resume();
		}
		else { isRunning = false; }
	}
}

void StateMachine::HandleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F11) {
			(showFPS) ? showFPS = false : showFPS = true;
		}

		currentState->HandleEvent(this, event);
		gui.handleEvent(event);
	}
}

void StateMachine::Update() {
	currentState->Update(this);
}

void StateMachine::Render() {
	window.clear();

	UIManager::Instance()->Render();
	currentState->Render();
	gui.draw();

	if (showFPS) { window.draw(fps); }

	window.display();
}

void StateMachine::Quit() {
	CleanUp();
	isRunning = false;
	window.close();
}

bool StateMachine::CheckState(State* state) {
	int counter{ 0 };

	for (auto statePtr : states) {
		if (state == statePtr) {
			return true;
		}
		else {
			counter++;
			if (counter == states.size()) {
				return false;
			}
		}
	}

	return false;
}

void StateMachine::UpdateFPS(unsigned int frameRate) {
	std::ostringstream ss;
	ss << frameRate;
	fps.setString(ss.str());
}