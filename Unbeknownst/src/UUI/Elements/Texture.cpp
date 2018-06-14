#include "UUI\Elements\Texture.hpp"

namespace uui {

	sf::Texture Texture::create(std::string fileName) {
		sf::Texture sfTexture;
		if (!sfTexture.loadFromFile("images/" + fileName)) {
			std::cout << "Failed to load texture file: " << fileName << std::endl;
		}

		return sfTexture;
	}

	sf::Texture Texture::create(const sf::Image& image, sf::IntRect rect) {
		sf::Texture sfTexture;
		if (!sfTexture.loadFromImage(image, rect)) {
			std::cout << "Failed to load texture from coordinates" << std::endl;
		}

		return sfTexture;
	}

}