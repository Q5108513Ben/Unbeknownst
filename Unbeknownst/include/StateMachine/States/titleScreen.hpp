#pragma once

#include "StateMachine\virtualState.hpp"
#include "UUI\UUI.hpp"

class TitleScreenState : public State {

	private:

		enum SubState {
			LoadGame,
			Extras,
			Options
		};

	public:

		void Initialise(sf::RenderWindow* window, tgui::Gui* gui, StateMachine* machine);
		void CleanUp();

		void Pause();
		void Resume();

		void HandleEvent(StateMachine* machine, sf::Event event);
		void Update(StateMachine* machine);
		void Render();

		static TitleScreenState* Instance() { return &titleScreen; }

	protected:

		TitleScreenState() {}

	private:

		// References

		static TitleScreenState titleScreen;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };

		sf::Image titleScreenWidgets;

		// Stored Data

		std::vector<sf::Sprite> spriteVector;
		std::vector<sf::Text> textVector;
		std::unordered_map<std::string, uui::TitleScreenButton> buttonMap;

		// Button functionality

		bool isFocusingButton{ false };
		std::string currentlyFocusedButton{ " " };

		void buttonFocused(std::string buttonName);
		void buttonUnfocused();
		void buttonClicked(StateMachine* machine);

		void changeSelectedButton(unsigned int direction);

		// Sub-state functionality

		bool subStateSelected{ false };
		SubState currentlySelectedSubState{};
		void changeSubState(SubState state);
		void removeSubState();

		// Misc functions

		void CreateSprite(std::string fileName);
		void CreateButtons(StateMachine* machine);
};