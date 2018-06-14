#pragma once

#include <TGUI\TGUI.hpp>

namespace uui {

	class Texture {

		public:

			static sf::Texture create(std::string fileName);
			static sf::Texture create(const sf::Image& image, sf::IntRect rect);

	};

}