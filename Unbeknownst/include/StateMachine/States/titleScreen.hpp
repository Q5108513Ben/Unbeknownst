#pragma once

#include "StateMachine\virtualState.hpp"
#include "UUI\UUI.hpp"

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

		sf::Image titleScreenWidgets;

		std::vector<sf::Sprite> spriteVector;
		std::vector<sf::Text> textVector;
		std::unordered_map<std::string, uui::TitleScreenButton> buttonMap;

		bool isFocusingButton{ false };
		std::string currentlyFocusedButton{ " " };

		void buttonFocused(std::string buttonName);
		void buttonUnfocused();
		void buttonClicked();

		void changeSelectedButton(unsigned int direction);

		void CreateSprite(std::string fileName);
		void CreateButtons();
};