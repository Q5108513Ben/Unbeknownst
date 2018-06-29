#pragma once

#include "StateMachine\virtualState.hpp"
#include "UUI\UUI.hpp"

class GameState : public State {

	public:

		void Initialise(sf::RenderWindow* window, tgui::Gui* gui, StateMachine* machine);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvent(StateMachine* machine, sf::Event event);
		void Update(StateMachine* machine);
		void Render();

		static GameState* Instance() { return &gameState; }

	protected:

		GameState() {}

	private:

		static GameState gameState;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };

};