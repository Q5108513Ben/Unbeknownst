#include "UUI\Elements\Texture.hpp"

namespace uui {

	sf::Texture Texture::create(std::string fileName) {
		sf::Texture sfTexture;
		if (!sfTexture.loadFromFile("images/" + fileName)) {
			std::cout << "Failed to load texture file: " << fileName << std::endl;
		}

		return sfTexture;
	}

}