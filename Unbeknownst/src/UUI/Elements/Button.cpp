#include "UUI\Elements\Button.hpp"
#include "UUI\ResourceManager.hpp"

namespace uui {

	sf::Text TitleScreenButton::create(Position buttonPosition, std::string text, Position textPosition) {
		tguiPicture = tguiPicture->create(uui::ResourceManager::Instance()->getTexture("ButtonNormal"));
		tguiPicture->setPosition(buttonPosition.x, buttonPosition.y);
		tguiPicture->scale(3, 3);
		
		sf::Text sfText;

		sfText.setFont(uui::ResourceManager::Instance()->getFont("UnbeknownstStnd"));
		sfText.setPosition((float)textPosition.x, (float)textPosition.y);
		sfText.setCharacterSize(24);
		sfText.setFillColor(sf::Color(204, 204, 204));
		sfText.setString(text); 
		
		return sfText;
	}

	void TitleScreenButton::setLinkedButtons(std::string up, std::string down, std::string left, std::string right) {
		nextButtonU = up;
		nextButtonD = down;
		nextButtonL = left;
		nextButtonR = right;
	}

	void TitleScreenButton::setIndex(unsigned int textIndex, unsigned int buttonIndex) {
		textID = textIndex;
		buttonID = buttonIndex;
	}

}