#pragma once

#include <TGUI\TGUI.hpp>
#include "UUI\Additional\Position.hpp"

namespace uui {

	class Button {
			
		public:

			Button() {};
			Button(tgui::Theme::Ptr theme);
			Button(tgui::Theme::Ptr theme, Position buttonPosition);
			Button(tgui::Theme::Ptr theme, Position buttonPosition, std::string text, Position textPosition);
			
			void setButton(const tgui::Button::Ptr& button);

			void setText(const std::string& text);
			void setTextFont(const sf::Font& font);
			void setTextColour(const sf::Color& colour);

			const tgui::Button::Ptr getButton() { return tguiButton; }
			const sf::Text& getText() { return sfText; }

		private:

			tgui::Button::Ptr tguiButton;
			sf::Text sfText;

	};

}