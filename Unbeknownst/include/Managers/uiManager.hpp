#pragma once

#include "StateMachine\stateMachine.hpp"

class UIManager {

	public:

		void Render();
		void LoadBaseUI(sf::RenderWindow* window, tgui::Gui* gui, StateMachine* machine);

		bool isGrabbed() { return grabbedWindow; }

		static UIManager* Instance() { return &uiManager; }
		
	protected:

		UIManager() {}

	private:

		void EnableMoveableWindow();
		sf::Vector2i grabbedOffset;
		bool grabbedWindow{ false };
		
		sf::RenderWindow* windowPtr{ nullptr };
		tgui::Gui* guiPtr{ nullptr };

		static UIManager uiManager;

};