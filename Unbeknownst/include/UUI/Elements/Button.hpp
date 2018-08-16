#pragma once

#include <TGUI\TGUI.hpp>
#include "UUI\Additional\Position.hpp"

namespace uui {

	class TitleScreenButton {
			
		public:

			TitleScreenButton() {}
			sf::Text create(Position buttonPosition, std::string text, Position textPosition, std::string defaultTexture);

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