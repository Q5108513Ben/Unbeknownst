#include "UUI\Elements\Button.hpp"

namespace uui {

	Button::Button(tgui::Theme::Ptr theme) {
		tguiButton = theme->load("Button");
		tguiButton->scale(3, 3);
	}

	Button::Button(tgui::Theme::Ptr theme, Position buttonPosition) {
		tguiButton = theme->load("Button");
		tguiButton->setPosition(buttonPosition.x, buttonPosition.y);
		tguiButton->scale(3, 3);
	}

	Button::Button(tgui::Theme::Ptr theme, Position buttonPosition, std::string text, Position textPosition) {
		tguiButton = theme->load("Button");
		tguiButton->setPosition(buttonPosition.x, buttonPosition.y);
		tguiButton->scale(3, 3);
		
		sfText.setString(text); 
		sfText.setCharacterSize(24);
		sfText.setPosition((float)textPosition.x, (float)textPosition.y);
	}

	void Button::setButton(const tgui::Button::Ptr& button) {
		tguiButton = button;
	}

	void Button::setText(const std::string& text) {
		sfText.setString(text);
	}

	void Button::setTextFont(const sf::Font& font) {
		sfText.setFont(font);
	}

	void Button::setTextColour(const sf::Color& colour) {

		sfText.setFillColor(colour);
	}

}