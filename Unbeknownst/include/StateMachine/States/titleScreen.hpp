#pragma once

#include "StateMachine\virtualState.hpp"

class TitleScreenState : public State {

	public:

		void Initialise(sf::RenderWindow* window, tgui::Gui* gui);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvent(StateMachine* machine, sf::Event event);
		void Update(StateMachine* machine);
		void Render(StateMachine* machine);

		static TitleScreenState* Instance() { return &titleScreen; }

	protected:

		TitleScreenState() {}

	private:

		static TitleScreenState titleScreen;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };

};