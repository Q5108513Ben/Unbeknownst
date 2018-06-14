#pragma once

#include <TGUI\TGUI.hpp>
#include "UUI\Additional\Position.hpp"

namespace uui {

	class TitleScreenButton {
			
		public:

			TitleScreenButton() {}
			sf::Text create(Position buttonPosition, std::string text, Position textPosition);

			const tgui::Picture::Ptr getPicture() { return tguiPicture; }

			const unsigned int& getTextID() { return textID; }
			const unsigned int& getButtonID() { return buttonID; }

			const std::string& getNextUp() { return nextButtonU; }
			const std::string& getNextDown() { return nextButtonD; }
			const std::string& getNextLeft() { return nextButtonL; }
			const std::string& getNextRight() { return nextButtonR; }

			void setLinkedButtons(std::string up, std::string down, std::string left, std::string right);
			void setIndex(unsigned int textIndex, unsigned int buttonIndex);

		private:

			std::string nextButtonU{ " " };
			std::string nextButtonD{ " " };
			std::string nextButtonL{ " " };
			std::string nextButtonR{ " " };
			
			tgui::Picture::Ptr tguiPicture;

			unsigned int textID{ 0 };
			unsigned int buttonID{ 0 };

	};

}

// Rework is almost complete, the mouse events are working as intended. Now I just need to 
// create functions in the TitleScreenState that handle keyboard events, this is where the 
// nextButton strings come into play as we can get the button we have selected through the 
// vector by using the currentlySelectedButton id. 
// Once we have the button we can get it's Up Down Left and Right strings that can be used
// here GuiRef->get(string) to alter the new button we want to select. The Text ID is the same
// as the Button ID so that shouldn't be a problem when altering the text.