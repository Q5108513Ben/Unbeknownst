#pragma once

#include <TGUI\TGUI.hpp>
#include "UUI\Additional\Position.hpp"

namespace uui {
	
	class Sprite {

		public:

			static sf::Sprite create(const sf::Texture& sfTexture);
			static sf::Sprite create(const sf::Texture& sfTexture, Position pos);

	};
}