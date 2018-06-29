#pragma once

#include "TitleScreen.hpp"
#include "UUI\UUI.hpp"

class OptionsState {

	public:

		void Initialise(sf::RenderWindow* window, tgui::Gui* gui);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvent(StateMachine* machine, sf::Event event);
		void Update(StateMachine* machine);
		void Render();

		static OptionsState* Instance() { return &optionsState; }

	protected:

		OptionsState() {}

	private:

		static OptionsState optionsState;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };

		std::vector<sf::Sprite> spriteVector;
		std::vector<sf::Text> textVector;

		void CreateButtons();
};