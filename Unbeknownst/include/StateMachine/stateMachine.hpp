#pragma once

#include "TGUI\TGUI.hpp"
#include <vector>

class State;
class StateMachine {

public:

	StateMachine();
	~StateMachine() {};

	void Initialise();
	void CleanUp();
	void PushState(State* state);
	void SwitchState(State* state);
	void PopState();

	void HandleEvents();
	void Update();
	void Render();

	void UpdateFPS(unsigned int frameRate);

	bool Running() { return isRunning; }
	void Quit();

private:

	std::vector<State*> states;
	State* currentState{ nullptr };
	State* previousState{ nullptr };

	sf::RenderWindow window;
	sf::RenderWindow* windowPtr{ nullptr };
	tgui::Gui gui;
	tgui::Gui* guiPtr{ nullptr };

	bool isRunning{ false };
	bool CheckState(State* state);

	sf::Text fps;
	bool showFPS{ false };

};