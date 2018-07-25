#pragma once

#include "TitleScreen.hpp"
#include "UUI\UUI.hpp"
#include "tinyxml2.h"

class OptionsState {

	private:

		enum Menu {
			Gameplay,
			Video,
			UI,
			Audio,
			KeyBind,
			Controller
		};

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

		// References

		static OptionsState optionsState;
		sf::RenderWindow* windowRef{ nullptr };
		tgui::Gui* guiRef{ nullptr };

		// Stored data

		std::vector<sf::Sprite> spriteVector;
		std::vector<sf::Text> textVector;
		std::unordered_map<std::string, uui::TitleScreenButton> buttonMap;

		// Button functionality

		bool isFocusingButton{ false };
		std::string currentlyFocusedButton{ " " };

		void buttonFocused(std::string buttonName);
		void buttonUnfocused();
		void buttonClicked();

		void changeSelectedButton(unsigned int direction);

		// Misc functions

		void CreateSprite(std::string fileName, uui::Position pos);
		void CreateButtons();

		// Menu System

		bool isMenuOpen{ false };
		Menu currentlyOpenedMenu;

		void RemoveMenu();

		sf::View menuView;

		// Key Binds Menu

		std::vector<sf::Text> textVectorKeyBind;
		std::unordered_map<std::string, uui::TitleScreenButton> buttonMapKeyBind;

		void CreateKeyBindsMenu();
		
};