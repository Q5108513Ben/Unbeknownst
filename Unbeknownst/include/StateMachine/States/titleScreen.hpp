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

		std::vector<sf::Sprite> spriteVector;
		std::vector<sf::Text> textVector;

		bool isFocusingButton{ false };
		unsigned int currentlyFocusedButton{ 0 };

		void buttonFocused(unsigned int textIndex, unsigned int buttonID);
		void buttonUnfocused(unsigned int textIndex);
		void buttonClicked();

		void CreateSprite(std::string fileName);
		void CreateButtons();
};

// Getting GUI navigation with the keyboard is going to be tricky. Obviously the simplest 
// solution is not doing it but if I can't get keyboard working then I definitely can't get
// a controller working which a lot of people would complain about if there was no controller 
// compatibility.

// For some reason when you use tgui::Button::focus() it does NOT use the "button down" sprite.
// Which is needed to make the button actually look like you are selecting it. The "button down"
// sprite is ONLY used when the mouse hovers over the button. But if we are using a keyboard
// to navigate we aren't going to hover the mouse over it unless we remove the user's control
// over their mouse.

// This actually would be a simple solution since when we press S or W to navigate the UI we
// would just move the cursor around to the button we want to select and it would work perfectly.
// However this means you can't navigate the menu with keyboard whilst moving the mouse around
// as your mouse is automatically moving onto the buttons.

// I need to look for a better solution that allows me to trigger the "button down" sprite
// without actually hovering the mouse over the button. If I can figure this out then we should
// be able to have mouse working alongside keyboard. If not I will have to remove control of
// the mouse.