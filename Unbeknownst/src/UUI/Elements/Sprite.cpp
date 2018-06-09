#include "UUI\Elements\Sprite.hpp"

namespace uui {

	sf::Sprite Sprite::create(const sf::Texture& sfTexture) {
		sf::Sprite sfSprite;
		sfSprite.setTexture(sfTexture);

		return sfSprite;
	}

	sf::Sprite Sprite::create(const sf::Texture& sfTexture, Position pos) {
		sf::Sprite sfSprite;
		sfSprite.setTexture(sfTexture);
		sfSprite.setPosition((float)pos.x, (float)pos.y);

		return sfSprite;
	}

}